#ifndef Personal_infoDto_hpp
#define Personal_infoDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Personal_infoDto : public oatpp::DTO {
  
  DTO_INIT(Personal_infoDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name, "name");
  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, phone, "phone");
  DTO_FIELD(String, address, "address");
  DTO_FIELD(String, summary, "summary");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* Personal_infoDto_hpp */
