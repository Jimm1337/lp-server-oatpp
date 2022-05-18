#include <oatpp-swagger/Controller.hpp>
#include <oatpp/network/Server.hpp>
#include "AppComponent.hpp"
#include "controller/lpController.hpp"

void run() {
  AppComponent                         components;

  static const oatpp::network::Address serverAddress = {
    "0.0.0.0", 8000, oatpp::network::Address::IP_4
  };

  OATPP_COMPONENT(network::RouterPtr_t, router);
  OATPP_COMPONENT(network::HandlerPtr_t, connectionHandler);
  OATPP_COMPONENT(network::ProviderPtr_t, connectionProvider);

  auto myController = std::make_shared<lpController>();
  auto swaggerController =
    oatpp::swagger::Controller::createShared(myController->getEndpoints());

  router->addController(myController);
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