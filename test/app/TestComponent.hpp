#ifndef LP_SERVER_OATPP_TESTCOMPONENT_HPP
#define LP_SERVER_OATPP_TESTCOMPONENT_HPP

#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/virtual_/client/ConnectionProvider.hpp>
#include <oatpp/network/virtual_/server/ConnectionProvider.hpp>
#include <oatpp/network/virtual_/Interface.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>

class TestComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)([] {
        return oatpp::network::virtual_::Interface::obtainShared("virtualhost");
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serVerConnectionProvider)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
        return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
        return oatpp::network::virtual_::client::ConnectionProvider::createShared(interface);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    // OWN COMPONENETS //


};

#endif //LP_SERVER_OATPP_TESTCOMPONENT_HPP