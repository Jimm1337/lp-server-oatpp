#include "service/testService.hpp"

oatpp::Object<DtoTest> testService::testSelect(const oatpp::Int32& testInt) {
    auto dbResult = m_database->testSelect(testInt);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status_t::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status_t::CODE_404, "Not Found.");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<DtoTest>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status_t::CODE_500, "Unknown Error.");
    return result[0];
}

v_int64 testService::testInsert(const oatpp::Object<DtoTest>& toInsert) {
    auto dbResult = m_database->testInsert(toInsert);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status_t::CODE_500, dbResult->getErrorMessage());

    return oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());
}

void testService::testDelete(const oatpp::Int32& testInt) {
    auto dbResult = m_database->testDelete(testInt);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status_t::CODE_500, dbResult->getErrorMessage());
}

oatpp::Object<DtoTestGpio> testService::testGpioWrite(const oatpp::Object<DtoTestGpio>& toWrite) {
    const auto& pin = toWrite->pin;
    const auto& state = toWrite->state;

    OATPP_ASSERT_HTTP(pin >= 0 && pin <= 31, Status_t::CODE_400, "Invalid pin number.");
    OATPP_ASSERT_HTTP(state == LOW || state == HIGH, Status_t::CODE_400, "Invalid state.");
    bcm2835_gpio_write(pin, state);
    return testGpioRead(pin);
}

oatpp::Object<DtoTestGpio> testService::testGpioRead(const oatpp::UInt8& pin) {
    OATPP_ASSERT_HTTP(pin >= 0 && pin <= 31, Status_t::CODE_400, "Invalid pin number.");
    auto result = DtoTestGpio::createShared();
    result->pin = pin;
    result->state = bcm2835_gpio_lev(pin);
    return result;
}

void testService::selectGpioInputMode(const oatpp::UInt8& pin) {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
}

void testService::selectGpioOutputMode(const oatpp::UInt8& pin) {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
}
