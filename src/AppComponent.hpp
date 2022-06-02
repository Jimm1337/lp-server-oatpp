#ifndef LP_SERVER_OATPP_APPCOMPONENT_HPP
#define LP_SERVER_OATPP_APPCOMPONENT_HPP

#include <oatpp-sqlite/orm.hpp>
#include <oatpp-swagger/Model.hpp>
#include <oatpp-swagger/Resources.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include "db/Database.hpp"

class AppComponent {
public:
  // BASE //

  OATPP_CREATE_COMPONENT(
    std::shared_ptr<oatpp::network::ServerConnectionProvider>,
    serverConnectionProvider)
  ([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
      { "0.0.0.0", 8000, oatpp::network::Address::IP_4 });
  }());

  OATPP_CREATE_COMPONENT(
    std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
  ([] { return oatpp::web::server::HttpRouter::createShared(); }());

  OATPP_CREATE_COMPONENT(
    std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    return oatpp::web::server::HttpConnectionHandler::createShared(router);
  }());

  // JSON //

  OATPP_CREATE_COMPONENT(
    std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
  ([] { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());

  // SWAGGER //

  OATPP_CREATE_COMPONENT(
    std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerInfo)
  ([] {
    oatpp::swagger::DocumentInfo::Builder builder;

    builder.setTitle("Serwer Linii Produkcyjnej")
      .setDescription("Dla SNS Automatyk PWR")
      .setVersion("0.0.1-dev")
      .setContactName("Oskar Gusta")
      .setLicenseName("GPL-3.0-or-later")
      .setLicenseUrl("https://www.gnu.org/licenses/gpl-3.0.en.html")
      .addServer(
        "http://"
        "localhost"
        ":8000",
        "localhost");

    return builder.build();
  }());

  OATPP_CREATE_COMPONENT(
    std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)
  ([] {
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());

  // SQLITE //

  OATPP_CREATE_COMPONENT(std::shared_ptr<network::Database>, Database)
  ([] {
    auto connectionProvider =
      std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);
    auto executor =
      std::make_shared<oatpp::sqlite::Executor>(connectionProvider);
    return std::make_shared<network::Database>(executor);
  }());
};

#endif // LP_SERVER_OATPP_APPCOMPONENT_HPP
