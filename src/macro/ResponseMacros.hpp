#ifndef LP_SERVER_OATPP_RESPONSEMACROS_HPP
#define LP_SERVER_OATPP_RESPONSEMACROS_HPP

#define RESPONSE_GET_OK(dto)                                                   \
  auto response = createDtoResponse(Status::CODE_200, dto);                    \
  response->putHeader(Header::CONTENT_TYPE, "application/vnd.api+json");       \
  return response

#define RESPONSE_POST_OK(dto) RESPONSE_GET_OK(dto)

#define RESPONSE_DELETE_OK()  return createResponse(Status::CODE_200, "")

#endif // LP_SERVER_OATPP_RESPONSEMACROS_HPP
