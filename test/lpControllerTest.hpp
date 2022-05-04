#ifndef LP_SERVER_OATPP_LPCONTROLLERTEST_HPP
#define LP_SERVER_OATPP_LPCONTROLLERTEST_HPP

#include <oatpp-test/UnitTest.hpp>

class lpControllerTest : public oatpp::test::UnitTest {
public:

    lpControllerTest() : UnitTest("TEST[lpControllerTest]") {}

    void onRun() override;
};

#endif //LP_SERVER_OATPP_LPCONTROLLERTEST_HPP
