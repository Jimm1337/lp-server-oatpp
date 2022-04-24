#ifndef LP_SERVER_OATPP_MYCONTROLLER_HPP
#define LP_SERVER_OATPP_MYCONTROLLER_HPP

#include "dto/DTOs.hpp"
#include "macro/ResponseMacros.hpp"
#include "macro/UtilityMacros.hpp"
#include "service/testService.hpp"

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include <bcm2835.h> //todo: test endpoints for gpio

// ENDPOINT PATHS DEFS //

#define TEST_SELECT "/testSelect"
#define STRUCTURE "/structure"
#define TEST_INSERT "/testInsert"
#define TEST_DELETE "/testDelete"

// ------------------ //

#include OATPP_CODEGEN_BEGIN(ApiController)

class MyController : public oatpp::web::server::api::ApiController {

    testService m_testService;
    //todo: add DbService
    //todo: error handling (look at example-crud/src/Error...)

public:
    explicit MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objMapper))
            : oatpp::web::server::api::ApiController(objMapper) {}


    ENDPOINT_INFO(structure) {
        info->summary = "Structure template";
        info->addResponse<Object<DtoData>>(Status::CODE_200, "application/vnd.api+json");
    }
    ENDPOINT("GET", STRUCTURE, structure,
             REQUEST(std::shared_ptr<IncomingRequest>, request)
    ) {
        auto dto = DtoData::createShared();
        dto->data["sample"] = "example";
        INJECT_SELF_LINK(dto, request, STRUCTURE);
        RESPONSE_GET_OK(dto);
    }

    ENDPOINT_INFO(testSelect) {
        info->summary = "Get by testInt";
        info->addResponse<Object<DtoData>>(Status::CODE_200, "application/vnd.api+json");
    }
    ENDPOINT("GET", TEST_SELECT"/{testInt}", testSelect,
             REQUEST(std::shared_ptr<IncomingRequest>, request),
             PATH(Int32, testInt)
    ) {
        auto dto = DtoTestResponse::createShared();
        dto->data["found"] = m_testService.testSelect(testInt);
        INJECT_SELF_LINK(dto, request, TEST_SELECT"/" + std::to_string(testInt));
        RESPONSE_GET_OK(dto);
    }

    ENDPOINT_INFO(testInsert) {
        info->summary = "Insert to test";
        info->addConsumes<Object<DtoTestRequest>>("application/vnd.api+json");
        info->addResponse<Object<DtoData>>(Status::CODE_200, "application/vnd.api+json");
    }
    ENDPOINT("POST", TEST_INSERT, testInsert,
             REQUEST(std::shared_ptr<IncomingRequest>, request),
             BODY_DTO(Object<DtoTestRequest>, body)
    ) {
        m_testService.testInsert(body->data);
        auto dto = DtoTestResponse::createShared();
        dto->data["created"] = m_testService.testSelect(body->data->testInt);
        INJECT_SELF_LINK(dto, request, TEST_INSERT);
        RESPONSE_POST_OK(dto);
    }

    ENDPOINT_INFO(testDelete) {
        info->summary = "Delete by testInt";
        info->addResponse<Object<DtoData>>(Status::CODE_200, "application/vnd.api+json");
    }
    ENDPOINT("DELETE", TEST_DELETE"/{testInt}", testDelete,
             PATH(Int32, testInt)
    ) {
        m_testService.testDelete(testInt);
        RESPONSE_DELETE_OK();
    }

    //todo: Endpoints here
};

#include OATPP_CODEGEN_END(ApiController)

#endif //LP_SERVER_OATPP_MYCONTROLLER_HPP
