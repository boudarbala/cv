
#ifndef SkillController_hpp
#define SkillController_hpp

#include "service/SkillService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Skill REST controller.
 */
class SkillController : public oatpp::web::server::api::ApiController {
public:
  SkillController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
private:
  SkillService m_SkillService; // Create Skill service.
public:

  static std::shared_ptr<SkillController> createShared(
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
  ){
    return std::make_shared<SkillController>(apiContentMappers);
  }
  
  ENDPOINT_INFO(createSkill) {
    info->summary = "Create new Skill";

    info->addConsumes<Object<SkillDto>>("application/json");

    info->addResponse<Object<SkillDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "Skills", createSkill,
           BODY_DTO(Object<SkillDto>, skillDto))
  {
    return createDtoResponse(Status::CODE_200, m_SkillService.createSkill(skillDto));
  }
  
  
  ENDPOINT_INFO(putSkill) {
    info->summary = "Update Skill by SkillId";

    info->addConsumes<Object<SkillDto>>("application/json");

    info->addResponse<Object<SkillDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["SkillId"].description = "Skill Identifier";
  }
  ENDPOINT("PUT", "Skills/{SkillId}", putSkill,
           PATH(Int32, SkillId),
           BODY_DTO(Object<SkillDto>, skillDto))
  {
    skillDto->id = SkillId;
    return createDtoResponse(Status::CODE_200, m_SkillService.updateSkill(skillDto));
  }
  
  
  ENDPOINT_INFO(getSkillById) {
    info->summary = "Get one Skill by SkillId";

    info->addResponse<Object<SkillDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["SkillId"].description = "Skill Identifier";
  }
  ENDPOINT("GET", "Skills/{SkillId}", getSkillById,
           PATH(Int32, skillId))
  {
    return createDtoResponse(Status::CODE_200, m_SkillService.getSkillById(skillId));
  }
  
  
  ENDPOINT_INFO(getSkills) {
    info->summary = "get all stored Skills";

    info->addResponse<oatpp::Object<SkillsPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "Skills/offset/{offset}/limit/{limit}", getSkills,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_SkillService.getAllSkills(offset, limit));
  }
  
  
  ENDPOINT_INFO(deleteSkill) {
    info->summary = "Delete Skill by SkillId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["SkillId"].description = "Skill Identifier";
  }
  ENDPOINT("DELETE", "Skills/{SkillId}", deleteSkill,
           PATH(Int32, skillId))
  {
    return createDtoResponse(Status::CODE_200, m_SkillService.deleteSkillById(skillId));
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* SkillController_hpp */