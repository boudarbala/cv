#ifndef SkillDto_hpp
#define SkillDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class SkillDto : public oatpp::DTO {
  
  DTO_INIT(SkillDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(Int32, personal_info_id, "personal_info_id");
  DTO_FIELD(String, skill, "skill");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* SkillDto_hpp */
