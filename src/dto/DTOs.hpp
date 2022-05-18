#ifndef LP_SERVER_OATPP_DTOS_HPP
#define LP_SERVER_OATPP_DTOS_HPP

#include <oatpp/core/data/mapping/type/Object.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>
#include "macro/UtilityMacros.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoTest : public oatpp::DTO {
  DTO_INIT(DtoTest, DTO)

  DTO_FIELD(String, testString);
  DTO_FIELD(Float32, testFloat);
  DTO_FIELD(Int32, testInt);
  DTO_FIELD(Boolean, testBool);
};

class DtoTestResponse : public oatpp::DTO {
  DTO_INIT(DtoTestResponse, DTO)

  DTO_FIELD(UnorderedFields<Object<DtoTest>>, data) = {};
  DTO_FIELD(UnorderedFields<String>, links)         = {};
};

class DtoTestRequest : public oatpp::DTO {
  DTO_INIT(DtoTestRequest, DTO)

  DTO_FIELD(Object<DtoTest>, data) = {};
};

class DtoTestGpio : public oatpp::DTO {
  DTO_INIT(DtoTestGpio, DTO)

  DTO_FIELD(UInt8, pin);
  DTO_FIELD(UInt8, state);
};

class DtoTestGpioResponse : public oatpp::DTO {
  DTO_INIT(DtoTestGpioResponse, DTO)

  DTO_FIELD(UnorderedFields<Object<DtoTestGpio>>, data) = {};
  DTO_FIELD(UnorderedFields<String>, links)             = {};
};

class DtoTestGpioRequest : public oatpp::DTO {
  DTO_INIT(DtoTestGpioRequest, DTO)

  DTO_FIELD(Object<DtoTestGpio>, data) = {};
};

class DtoData : public oatpp::DTO {
  DTO_INIT(DtoData, DTO)

  DTO_FIELD(UnorderedFields<String>, data)  = {};
  DTO_FIELD(UnorderedFields<String>, links) = {};
};

class DtoErrors : public oatpp::DTO {
  DTO_INIT(DtoErrors, DTO)

  DTO_FIELD(UnorderedFields<String>, errors) = {};
  DTO_FIELD(UnorderedFields<String>, links)  = {};
};

#include OATPP_CODEGEN_END(DTO)

#endif // LP_SERVER_OATPP_DTOS_HPP
