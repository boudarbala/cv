
#ifndef CRUD_PAGEDTO_HPP
#define CRUD_PAGEDTO_HPP

#include "EducationDto.hpp"
#include "ExperienceDto.hpp"
#include "SkillDto.hpp"
#include "Personal_infoDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

  DTO_INIT(PageDto, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class EducationsPageDto : public PageDto<oatpp::Object<EducationDto>> {

  DTO_INIT(EducationsPageDto, PageDto<oatpp::Object<EducationDto>>)

};
class ExperiencesPageDto : public PageDto<oatpp::Object<ExperienceDto>> {

  DTO_INIT(ExperiencesPageDto, PageDto<oatpp::Object<ExperienceDto>>)

};
class Personal_infosPageDto : public PageDto<oatpp::Object<Personal_infoDto>> {

  DTO_INIT(Personal_infosPageDto, PageDto<oatpp::Object<Personal_infoDto>>)

};
class SkillsPageDto : public PageDto<oatpp::Object<SkillDto>> {

  DTO_INIT(SkillsPageDto, PageDto<oatpp::Object<SkillDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif //CRUD_PAGEDTO_HPP