#ifndef LP_SERVER_OATPP_TESTSERVICE_HPP
#define LP_SERVER_OATPP_TESTSERVICE_HPP

#include <gpiod.h>
#include <oatpp-sqlite/Utils.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include "db/Database.hpp"
#include "dto/DTOs.hpp"

class testService {
  constexpr static auto GPIO_CHIP_NAME = "gpiochip0";

  using Status  = oatpp::web::protocol::http::Status;
  using ChipPtr = std::unique_ptr<gpiod_chip, decltype([](gpiod_chip* ptr) {
                                    if (ptr != nullptr) {
                                      gpiod_chip_close(ptr);
                                    }
                                  })>;
  using LinePtr = std::unique_ptr<gpiod_line, decltype([](gpiod_line* ptr) {
                                    if (ptr != nullptr) {
                                      gpiod_line_release(ptr);
                                    }
                                  })>;

  OATPP_COMPONENT(std::shared_ptr<network::Database>, m_database);

  ChipPtr m_gpioChip;

public:
  testService();

  // db //

  [[nodiscard]] oatpp::Object<DtoTest> testSelect(const oatpp::Int32& testInt);
  v_int64 testInsert(const oatpp::Object<DtoTest>& toInsert);
  void    testDelete(const oatpp::Int32& testInt);

  // gpio //

  [[nodiscard]] oatpp::Object<DtoTestGpio> testGpioWrite(
    const oatpp::Object<DtoTestGpio>& toWrite);
  [[nodiscard]] oatpp::Object<DtoTestGpio> testGpioRead(
    const oatpp::UInt8& pin);
};

#endif // LP_SERVER_OATPP_TESTSERVICE_HPP
