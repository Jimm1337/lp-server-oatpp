#ifndef LP_SERVER_OATPP_MYCONTROLLERTEST_HPP
#define LP_SERVER_OATPP_MYCONTROLLERTEST_HPP

#include <oatpp-test/UnitTest.hpp>

class MyControllerTest : public oatpp::test::UnitTest {
public:

    MyControllerTest() : UnitTest("TEST[MyControllerTest]") {}

    void onRun() override;
};

#endif //LP_SERVER_OATPP_MYCONTROLLERTEST_HPP
