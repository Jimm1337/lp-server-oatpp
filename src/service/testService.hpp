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

  using Status_t = oatpp::web::protocol::http::Status;

  OATPP_COMPONENT(std::shared_ptr<network::Database>, m_database);

  gpiod_chip* m_gpioChip;

public:
  testService();
  ~testService();

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
