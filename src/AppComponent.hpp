#ifndef LP_SERVER_OATPP_APPCOMPONENT_HPP
#define LP_SERVER_OATPP_APPCOMPONENT_HPP

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/core/macro/component.hpp>

namespace network {
    using ProviderPtr_t = std::shared_ptr<oatpp::network::ServerConnectionProvider>;
    using RouterPtr_t = std::shared_ptr<oatpp::web::server::HttpRouter>;
    using HandlerPtr_t = std::shared_ptr<oatpp::network::ConnectionHandler>;
    using MapperPtr_t = std::shared_ptr<oatpp::data::mapping::ObjectMapper>;
}

class AppComponent {
public:
    OATPP_CREATE_COMPONENT(network::ProviderPtr_t, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
                {"localhost", 8000, oatpp::network::Address::IP_4}
        );
    }());

    OATPP_CREATE_COMPONENT(network::RouterPtr_t, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(network::HandlerPtr_t, serverConnectionHandler)([] {
        OATPP_COMPONENT(network::RouterPtr_t, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    OATPP_CREATE_COMPONENT(network::MapperPtr_t, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    // OWN COMPONENETS //


};

#endif //LP_SERVER_OATPP_APPCOMPONENT_HPP
