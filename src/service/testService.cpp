#include "service/testService.hpp"

testService::testService():
  m_gpioChip(gpiod_chip_open_by_name(GPIO_CHIP_NAME)) {
}

oatpp::Object<DtoTest> testService::testSelect(const oatpp::Int32& testInt) {
  const auto dbResult = m_database->testSelect(testInt);
  OATPP_ASSERT_HTTP(
    dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Not Found.");

  const auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<DtoTest>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown Error.");
  return result[0];
}

v_int64 testService::testInsert(const oatpp::Object<DtoTest>& toInsert) {
  const auto dbResult = m_database->testInsert(toInsert);
  OATPP_ASSERT_HTTP(
    dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  return oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());
}

void testService::testDelete(const oatpp::Int32& testInt) {
  const auto dbResult = m_database->testDelete(testInt);
  OATPP_ASSERT_HTTP(
    dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
}

oatpp::Object<DtoTestGpio> testService::testGpioWrite(
  const oatpp::Object<DtoTestGpio>& toWrite) {
  OATPP_ASSERT_HTTP(
    m_gpioChip != nullptr, Status::CODE_500, "Error opening chip.");

  LinePtr reqLine{ gpiod_chip_get_line(m_gpioChip.get(), toWrite->pin) };
  OATPP_ASSERT_HTTP(
    reqLine != nullptr, Status::CODE_500, "Error getting line.");

  const int outputReqStatus =
    gpiod_line_request_output(reqLine.get(), "httpClient", 0);
  OATPP_ASSERT_HTTP(
    outputReqStatus != -1, Status::CODE_500, "Error requesting output mode.");

  const int outputStatus = gpiod_line_set_value(reqLine.get(), toWrite->state);
  OATPP_ASSERT_HTTP(
    outputStatus != -1, Status::CODE_500, "Error writing value.");

  OATPP_LOGI(
    "gpiod",
    "Written value %hhu from pin %hhu",
    toWrite->state.getValue(0),
    toWrite->pin.getValue(0));

  auto ret = [&] {
    auto dto   = DtoTestGpio::createShared();
    dto->pin   = toWrite->pin;
    dto->state = toWrite->state;
    return dto;
  }();
  return ret;
}

oatpp::Object<DtoTestGpio> testService::testGpioRead(const oatpp::UInt8& pin) {
  OATPP_ASSERT_HTTP(
    m_gpioChip != nullptr, Status::CODE_500, "Error opening chip.");

  LinePtr reqLine{ gpiod_chip_get_line(m_gpioChip.get(), pin) };
  OATPP_ASSERT_HTTP(
    reqLine != nullptr, Status::CODE_500, "Error getting line.");

  const int inputReqStatus =
    gpiod_line_request_input(reqLine.get(), "httpClient");
  OATPP_ASSERT_HTTP(
    inputReqStatus != -1, Status::CODE_500, "Error requesting input mode.");

  int readValue = gpiod_line_get_value(reqLine.get());
  OATPP_ASSERT_HTTP(readValue != -1, Status::CODE_500, "Error reading value.");

  OATPP_LOGI(
    "gpiod", "Read value %hhu from pin %hhu", readValue, pin.getValue(0));

  auto ret = [&] {
    auto dto   = DtoTestGpio::createShared();
    dto->pin   = pin;
    dto->state = static_cast<std::uint8_t>(readValue);
    return dto;
  }();
  return ret;
}
