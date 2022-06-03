#ifndef LP_SERVER_OATPP_LPCONTROLLER_HPP
#define LP_SERVER_OATPP_LPCONTROLLER_HPP

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include "dto/DTOs.hpp"
#include "macro/ResponseMacros.hpp"
#include "macro/UtilityMacros.hpp"
#include "service/testService.hpp"

// ENDPOINT PATHS DEFS //

#define TEST_SELECT     "/testSelect"
#define STRUCTURE       "/structure"
#define TEST_INSERT     "/testInsert"
#define TEST_DELETE     "/testDelete"
#define TEST_GPIO_WRITE "/testGpioWrite"
#define TEST_GPIO_READ  "/testGpioRead"

// ------------------ //

#include OATPP_CODEGEN_BEGIN(ApiController)

class lpController : public oatpp::web::server::api::ApiController {
  testService m_testService;
  // todo: add other services

public:
  explicit lpController(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objMapper)):
    oatpp::web::server::api::ApiController(objMapper) {
  }

  ENDPOINT_INFO(structure) {
    info->summary = "Structure template";
    info->addResponse<Object<DtoData>>(
      Status::CODE_200, "application/vnd.api+json");
  }
  ENDPOINT(
    "GET",
    STRUCTURE,
    structure,
    REQUEST(std::shared_ptr<IncomingRequest>, request)) {
    const auto ret = [&] {
      auto dto            = DtoData::createShared();
      dto->data["sample"] = "example";
      INJECT_SELF_LINK(dto, request, STRUCTURE);
      return dto;
    }();
    RESPONSE_GET_OK(ret);
  }

  ENDPOINT_INFO(testSelect) {
    info->summary = "Get by testInt";
    info->addResponse<Object<DtoData>>(
      Status::CODE_200, "application/vnd.api+json");
  }
  ENDPOINT(
    "GET",
    TEST_SELECT "/{testInt}",
    testSelect,
    REQUEST(std::shared_ptr<IncomingRequest>, request),
    PATH(Int32, testInt)) {
    const auto ret = [&] {
      auto dto           = DtoTestResponse::createShared();
      dto->data["found"] = m_testService.testSelect(testInt);
      INJECT_SELF_LINK(dto, request, TEST_SELECT "/" + std::to_string(testInt));
      return dto;
    }();
    RESPONSE_GET_OK(ret);
  }

  ENDPOINT_INFO(testInsert) {
    info->summary = "Insert to test";
    info->addConsumes<Object<DtoTestRequest>>("application/vnd.api+json");
    info->addResponse<Object<DtoData>>(
      Status::CODE_200, "application/vnd.api+json");
  }
  ENDPOINT(
    "POST",
    TEST_INSERT,
    testInsert,
    REQUEST(std::shared_ptr<IncomingRequest>, request),
    BODY_DTO(Object<DtoTestRequest>, body)) {
    m_testService.testInsert(body->data);
    const auto ret = [&] {
      auto dto             = DtoTestResponse::createShared();
      dto->data["created"] = m_testService.testSelect(body->data->testInt);
      INJECT_SELF_LINK(dto, request, TEST_INSERT);
      return dto;
    }();
    RESPONSE_POST_OK(ret);
  }

  ENDPOINT_INFO(testDelete) {
    info->summary = "Delete by testInt";
    info->addResponse<Object<DtoData>>(
      Status::CODE_200, "application/vnd.api+json");
  }
  ENDPOINT(
    "DELETE", TEST_DELETE "/{testInt}", testDelete, PATH(Int32, testInt)) {
    m_testService.testDelete(testInt);
    RESPONSE_DELETE_OK();
  }

  ENDPOINT_INFO(testGpioRead) {
    info->summary = "Read from gpio pin";
    info->addResponse<Object<DtoData>>(
      Status::CODE_200, "application/vnd.api+json");
  }
  ENDPOINT(
    "GET",
    TEST_GPIO_READ "/{pin}",
    testGpioRead,
    REQUEST(std::shared_ptr<IncomingRequest>, request),
    PATH(UInt8, pin)) {
    const auto ret = [&] {
      auto dto          = DtoTestGpioResponse::createShared();
      dto->data["read"] = m_testService.testGpioRead(pin);
      INJECT_SELF_LINK(dto, request, TEST_GPIO_READ);
      return dto;
    }();
    RESPONSE_GET_OK(ret);
  }

  ENDPOINT_INFO(testGpioWrite) {
    info->summary = "Write to gpio pin";
    info->addConsumes<Object<DtoTestGpioRequest>>("application/vnd.api+json");
    info->addResponse<Object<DtoData>>(
      Status::CODE_200, "application/vnd.api+json");
  }
  ENDPOINT(
    "POST",
    TEST_GPIO_WRITE,
    testGpioWrite,
    REQUEST(std::shared_ptr<IncomingRequest>, request),
    BODY_DTO(Object<DtoTestGpioRequest>, body)) {
    const auto ret = [&] {
      auto dto             = DtoTestGpioResponse::createShared();
      dto->data["written"] = m_testService.testGpioWrite(body->data);
      INJECT_SELF_LINK(dto, request, TEST_GPIO_READ);
      return dto;
    }();
    RESPONSE_GET_OK(ret);
  }

  // todo: Endpoints here
};

#include OATPP_CODEGEN_END(ApiController)

#endif // LP_SERVER_OATPP_LPCONTROLLER_HPP
