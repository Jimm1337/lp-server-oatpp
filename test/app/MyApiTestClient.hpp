#ifndef LP_SERVER_OATPP_MYAPITESTCLIENT_HPP
#define LP_SERVER_OATPP_MYAPITESTCLIENT_HPP

#include <oatpp/web/client/ApiClient.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(ApiClient)

class MyApiTestClient : public oatpp::web::client::ApiClient {
API_CLIENT_INIT(MyApiTestClient);

    API_CALL("GET", "/hello", getHello);

    //todo: Add more api calls here
};

#include OATPP_CODEGEN_END(ApiClient)

#endif //LP_SERVER_OATPP_MYAPITESTCLIENT_HPP
