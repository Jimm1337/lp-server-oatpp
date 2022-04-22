#ifndef LP_SERVER_OATPP_DTOS_HPP
#define LP_SERVER_OATPP_DTOS_HPP

#include <oatpp/core/data/mapping/type/Object.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO {
    DTO_INIT(MessageDto, DTO)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

#endif //LP_SERVER_OATPP_DTOS_HPP
