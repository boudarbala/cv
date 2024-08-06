#ifndef EducationDto_hpp
#define EducationDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class EducationDto : public oatpp::DTO {
  
  DTO_INIT(EducationDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, institution, "institution");
  DTO_FIELD(String, degree, "degree");
  DTO_FIELD(String, start_date, "start_date");
  DTO_FIELD(String, end_date, "end_date");
  DTO_FIELD(String, description, "description");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* EducationDto_hpp */
