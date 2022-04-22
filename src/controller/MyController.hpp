#ifndef LP_SERVER_OATPP_MYCONTROLLER_HPP
#define LP_SERVER_OATPP_MYCONTROLLER_HPP

#include "dto/DTOs.hpp"

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

class MyController : public oatpp::web::server::api::ApiController {
public:
    explicit MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objMapper))
    : oatpp::web::server::api::ApiController(objMapper) {}

public:

    ENDPOINT("GET", "/hello", root) {
        auto dto = MessageDto::createShared();
        dto->statusCode = 200;
        dto->message = "Hello Worrrld";
        return createDtoResponse(Status::CODE_200, dto);
    }

    //todo: Endpoints here
};

#include OATPP_CODEGEN_END(ApiController)

#endif //LP_SERVER_OATPP_MYCONTROLLER_HPP
