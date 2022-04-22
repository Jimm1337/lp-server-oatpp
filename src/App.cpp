#include "controller/MyController.hpp"
#include "AppComponent.hpp"

#include <oatpp/network/Server.hpp>
#include <oatpp-swagger/Controller.hpp>

void run() {

    AppComponent components;

    static const oatpp::network::Address serverAddress = {"localhost", 8000, oatpp::network::Address::IP_4};

    OATPP_COMPONENT(network::RouterPtr_t, router);
    OATPP_COMPONENT(network::HandlerPtr_t, connectionHandler);
    OATPP_COMPONENT(network::ProviderPtr_t, connectionProvider);

    auto myController = std::make_shared<MyController>();
    auto swaggerController = oatpp::swagger::Controller::createShared(myController->getEndpoints());

    router->addController(myController);
    router->addController(swaggerController);

    oatpp::network::Server server{connectionProvider, connectionHandler};

    OATPP_LOGI("MyApp", "Server Running on port %s", connectionProvider->getProperty("port").getData());

    server.run();
}

int main() {
    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();

    return 0;
}
