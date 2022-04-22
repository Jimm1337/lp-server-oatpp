#ifndef LP_SERVER_OATPP_MYCONTROLLER_HPP
#define LP_SERVER_OATPP_MYCONTROLLER_HPP

#include "dto/DTOs.hpp"
#include "ResponseMacros.hpp"
#include "UtilityMacros.hpp"

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#define PATH_STRUCTURE "/structure"

#include OATPP_CODEGEN_BEGIN(ApiController)

class MyController : public oatpp::web::server::api::ApiController {
public:
    explicit MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objMapper))
    : oatpp::web::server::api::ApiController(objMapper) {}

public:

    ENDPOINT_INFO(structure) {
        info->summary = "Structure template";
        info->addResponse<Object<DtoData>>(Status::CODE_200, "application/vnd.api+json");
    }
    ENDPOINT("GET", PATH_STRUCTURE, structure, REQUEST(std::shared_ptr<IncomingRequest>, request)) {
        auto dto = DtoData::createShared();
        dto->data["sample"] = "example";
        INJECT_SELF_LINK(dto, request, PATH_STRUCTURE);
        RESPONSE_GET_OK(dto);
    }

    //todo: Endpoints here
};

#include OATPP_CODEGEN_END(ApiController)

#endif //LP_SERVER_OATPP_MYCONTROLLER_HPP
