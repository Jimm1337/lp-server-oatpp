#include "service/testService.hpp"

oatpp::Object<DtoTest> testService::testSelect(const oatpp::Int32& testInt) {
  auto dbResult = m_database->testSelect(testInt);
  OATPP_ASSERT_HTTP(
    dbResult->isSuccess(), Status_t::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(
    dbResult->hasMoreToFetch(), Status_t::CODE_404, "Not Found.");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<DtoTest>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status_t::CODE_500, "Unknown Error.");
  return result[0];
}

v_int64 testService::testInsert(const oatpp::Object<DtoTest>& toInsert) {
  auto dbResult = m_database->testInsert(toInsert);
  OATPP_ASSERT_HTTP(
    dbResult->isSuccess(), Status_t::CODE_500, dbResult->getErrorMessage());

  return oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());
}

void testService::testDelete(const oatpp::Int32& testInt) {
  auto dbResult = m_database->testDelete(testInt);
  OATPP_ASSERT_HTTP(
    dbResult->isSuccess(), Status_t::CODE_500, dbResult->getErrorMessage());
}

oatpp::Object<DtoTestGpio> testService::testGpioWrite(
  const oatpp::Object<DtoTestGpio>& toWrite) {
  // todo: use gpiod
}

oatpp::Object<DtoTestGpio> testService::testGpioRead(const oatpp::UInt8& pin) {
  // todo: use gpiod
}

void testService::selectGpioInputMode(const oatpp::UInt8& pin) {
  // todo: use gpiod
}

void testService::selectGpioOutputMode(const oatpp::UInt8& pin) {
  // todo: use gpiod
}
