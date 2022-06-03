#ifndef LP_SERVER_OATPP_APITESTCLIENT_HPP
#define LP_SERVER_OATPP_APITESTCLIENT_HPP

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/web/client/ApiClient.hpp>

#include OATPP_CODEGEN_BEGIN(ApiClient)

class ApiTestClient : public oatpp::web::client::ApiClient {
  API_CLIENT_INIT(ApiTestClient);

  API_CALL("GET", "/hello", getHello);

  // todo: Add more api calls here
};

#include OATPP_CODEGEN_END(ApiClient)

#endif // LP_SERVER_OATPP_APITESTCLIENT_HPP
