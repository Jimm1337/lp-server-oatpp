#ifndef LP_SERVER_OATPP_TESTSERVICE_HPP
#define LP_SERVER_OATPP_TESTSERVICE_HPP

#include "db/Database.hpp"
#include "dto/DTOs.hpp"

#include <oatpp/web/protocol/http/Http.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp-sqlite/Utils.hpp>

#include <bcm2835.h>

class testService {
    using Status_t = oatpp::web::protocol::http::Status;

    OATPP_COMPONENT(std::shared_ptr<network::Database>, m_database);

public:
    // db //

    [[nodiscard]] oatpp::Object<DtoTest> testSelect(const oatpp::Int32& testInt);
    v_int64 testInsert(const oatpp::Object<DtoTest>& toInsert);
    void testDelete(const oatpp::Int32& testInt);

    // gpio //

    [[nodiscard]] static oatpp::Object<DtoTestGpio> testGpioWrite(const oatpp::Object<DtoTestGpio>& toWrite);
    [[nodiscard]] static oatpp::Object<DtoTestGpio> testGpioRead(const oatpp::UInt8& pin);
    static void selectGpioInputMode(const oatpp::UInt8& pin);
    static void selectGpioOutputMode(const oatpp::UInt8& pin);
};

#endif //LP_SERVER_OATPP_TESTSERVICE_HPP
