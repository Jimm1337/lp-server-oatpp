#include "controller/lpController.hpp"
#include "AppComponent.hpp"

#include <oatpp/network/Server.hpp>
#include <oatpp-swagger/Controller.hpp>

#include <bcm2835.h>

void run() {

    AppComponent components;

    static const oatpp::network::Address serverAddress = {SERVER_HOST_IP, 8000, oatpp::network::Address::IP_4};

    OATPP_COMPONENT(network::RouterPtr_t, router);
    OATPP_COMPONENT(network::HandlerPtr_t, connectionHandler);
    OATPP_COMPONENT(network::ProviderPtr_t, connectionProvider);

    auto myController = std::make_shared<lpController>();
    auto swaggerController = oatpp::swagger::Controller::createShared(myController->getEndpoints());

    router->addController(myController);
    router->addController(swaggerController);

    oatpp::network::Server server{connectionProvider, connectionHandler};

    OATPP_LOGI("MyApp", "Server Running on port %s", connectionProvider->getProperty("port").getData());

    server.run();
}

int main() {
    bcm2835_set_debug(1); //todo: comment out in release
    bcm2835_init();
    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();
    bcm2835_close();

    return 0;
}

//todo: write tests for gpio and db