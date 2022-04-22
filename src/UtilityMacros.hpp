#ifndef LP_SERVER_OATPP_UTILITYMACROS_HPP
#define LP_SERVER_OATPP_UTILITYMACROS_HPP

#define INJECT_SELF_LINK(dto, request, endpointPath) \
dto->links["self"] = "http://" + request->getHeaders().get("Host") + endpointPath


#endif //LP_SERVER_OATPP_UTILITYMACROS_HPP
