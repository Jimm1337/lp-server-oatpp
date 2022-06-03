#include <oatpp-swagger/Controller.hpp>
#include <oatpp/network/Server.hpp>
#include "AppComponent.hpp"
#include "controller/lpController.hpp"

void run() {
  AppComponent components;

  // static const oatpp::network::Address serverAddress = {
  //   "0.0.0.0", 8000, oatpp::network::Address::IP_4
  // };

  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
  OATPP_COMPONENT(
    std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
  OATPP_COMPONENT(
    std::shared_ptr<oatpp::network::ServerConnectionProvider>,
    connectionProvider);

  auto controller = std::make_shared<lpController>();
  auto swaggerController =
    oatpp::swagger::Controller::createShared(controller->getEndpoints());

  router->addController(controller);
  router->addController(swaggerController);

  oatpp::network::Server server{ connectionProvider, connectionHandler };

  OATPP_LOGI(
    "MyApp",
    "Server Running on %s:%s",
    connectionProvider->getProperty("host").getData(),
    connectionProvider->getProperty("port").getData());

  server.run();
}

int main() {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();

  return 0;
}

// todo: write tests for gpio and db