#include "lpControllerTest.hpp"
#include <oatpp-test/web/ClientServerTestRunner.hpp>
#include <oatpp/web/client/HttpRequestExecutor.hpp>
#include "app/ApiTestClient.hpp"
#include "app/TestComponent.hpp"
#include "controller/lpController.hpp"

void lpControllerTest::onRun() {
  TestComponent component;

  oatpp::test::web::ClientServerTestRunner runner;

  runner.addController(std::make_shared<lpController>());

  runner.run(
    [this, &runner] {
    // OATPP_COMPONENT(
    //   std::shared_ptr<oatpp::network::ClientConnectionProvider>,
    //   clientConnectionProvider);
    // OATPP_COMPONENT(
    //   std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objMapper);
    //
    // auto requestExecutor =
    //   oatpp::web::client::HttpRequestExecutor::createShared(
    //     clientConnectionProvider);
    // auto client   = ApiTestClient::createShared(requestExecutor,
    // objMapper); auto response = client->getHello();
    //
    // OATPP_ASSERT(response->getStatusCode() == 200);
    //
    // auto message =
    //   response->readBodyToDto<oatpp::Object<MessageDto>>(objMapper.get());
    //
    // OATPP_ASSERT(message);
    // OATPP_ASSERT(message->statusCode == 200);
    // OATPP_ASSERT(message->message == "Hello Worrrld");
    },
    std::chrono::minutes(10));

  std::this_thread::sleep_for(std::chrono::seconds(1));
}