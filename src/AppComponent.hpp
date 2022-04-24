#ifndef LP_SERVER_OATPP_APPCOMPONENT_HPP
#define LP_SERVER_OATPP_APPCOMPONENT_HPP

#include "db/Database.hpp"

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp-swagger/Model.hpp>
#include <oatpp-swagger/Resources.hpp>
#include <oatpp-sqlite/orm.hpp>

namespace network {
    using ProviderPtr_t = std::shared_ptr<oatpp::network::ServerConnectionProvider>;
    using RouterPtr_t = std::shared_ptr<oatpp::web::server::HttpRouter>;
    using HandlerPtr_t = std::shared_ptr<oatpp::network::ConnectionHandler>;
    using MapperPtr_t = std::shared_ptr<oatpp::data::mapping::ObjectMapper>;
    using SwaggerInfo_t = std::shared_ptr<oatpp::swagger::DocumentInfo>;
    using SwaggerResources_t = std::shared_ptr<oatpp::swagger::Resources>;
    using DbClient_t = std::shared_ptr<Database>;
}

class AppComponent {
public:

    // BASE //

    OATPP_CREATE_COMPONENT(network::ProviderPtr_t, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
                {SERVER_HOST_IP, 8000, oatpp::network::Address::IP_4}
        );
    }());

    OATPP_CREATE_COMPONENT(network::RouterPtr_t, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(network::HandlerPtr_t, serverConnectionHandler)([] {
        OATPP_COMPONENT(network::RouterPtr_t, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    // JSON //

    OATPP_CREATE_COMPONENT(network::MapperPtr_t, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    // SWAGGER //

    OATPP_CREATE_COMPONENT(network::SwaggerInfo_t, swaggerInfo)([] {
        oatpp::swagger::DocumentInfo::Builder builder;

        builder
            .setTitle("Serwer Linii Produkcyjnej")
            .setDescription("Dla SNS Automatyk PWR")
            .setVersion("0.0.1-dev")
            .setContactName("Oskar Gusta")
            .setLicenseName("GPL-3.0-or-later")
            .setLicenseUrl("https://www.gnu.org/licenses/gpl-3.0.en.html")
            .addServer("http://" SERVER_HOST_IP ":8000", "Default location");

        return builder.build();
    }());

    OATPP_CREATE_COMPONENT(network::SwaggerResources_t, swaggerResources)([] {
        return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());

    // SQLITE //

    OATPP_CREATE_COMPONENT(network::DbClient_t, Database)([] {
        auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);
        auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);
        return std::make_shared<network::Database>(executor);
    }());
};

#endif //LP_SERVER_OATPP_APPCOMPONENT_HPP
