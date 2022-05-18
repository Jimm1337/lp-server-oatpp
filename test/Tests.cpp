#include <iostream>
#include "lpControllerTest.hpp"

void runTests() {
  OATPP_RUN_TEST(lpControllerTest);

  // todo: add tests
  // OATPP_RUN_TEST(MyAnotherTest);
}

int main() {
  oatpp::base::Environment::init();

  runTests();

  std::cout << "\nEnvironment:\n"
            << "objectsCount = " << oatpp::base::Environment::getObjectsCount()
            << '\n'
            << "objectsCreated = "
            << oatpp::base::Environment::getObjectsCreated() << '\n';

  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);

  oatpp::base::Environment::destroy();

  return 0;
}