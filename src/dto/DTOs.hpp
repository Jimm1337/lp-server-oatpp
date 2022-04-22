#ifndef LP_SERVER_OATPP_DTOS_HPP
#define LP_SERVER_OATPP_DTOS_HPP

#include <oatpp/core/data/mapping/type/Object.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoData : public oatpp::DTO {
    DTO_INIT(DtoData, DTO)

    DTO_FIELD(UnorderedFields<String>, data) = {};
    DTO_FIELD(UnorderedFields<String>, links) = {};
};

class DtoErrors : public oatpp::DTO {
    DTO_INIT(DtoErrors, DTO)

    DTO_FIELD(UnorderedFields<String>, errors) = {};
    DTO_FIELD(UnorderedFields<String>, links) = {};
};

#include OATPP_CODEGEN_END(DTO)

#endif //LP_SERVER_OATPP_DTOS_HPP
