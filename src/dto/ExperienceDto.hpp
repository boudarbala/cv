#ifndef ExperienceDto_hpp
#define ExperienceDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ExperienceDto : public oatpp::DTO {
  
  DTO_INIT(ExperienceDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, job_title, "job_title");
  DTO_FIELD(String, company, "company");
  DTO_FIELD(String, start_date, "start_date");
  DTO_FIELD(String, end_date, "end_date");
  DTO_FIELD(String, description, "description");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* ExperienceDto_hpp */
