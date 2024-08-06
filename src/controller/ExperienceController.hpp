
#ifndef ExperienceController_hpp
#define ExperienceController_hpp

#include "service/ExperienceService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Experience REST controller.
 */
class ExperienceController : public oatpp::web::server::api::ApiController {
public:
  ExperienceController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
private:
  ExperienceService m_ExperienceService; // Create Experience service.
public:

  static std::shared_ptr<ExperienceController> createShared(
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
  ){
    return std::make_shared<ExperienceController>(apiContentMappers);
  }
  
  ENDPOINT_INFO(createExperience) {
    info->summary = "Create new Experience";

    info->addConsumes<Object<ExperienceDto>>("application/json");

    info->addResponse<Object<ExperienceDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "Experiences", createExperience,
           BODY_DTO(Object<ExperienceDto>, ExperienceDto))
  {
    return createDtoResponse(Status::CODE_200, m_ExperienceService.createExperience(ExperienceDto));
  }
  
  
  ENDPOINT_INFO(putExperience) {
    info->summary = "Update Experience by ExperienceId";

    info->addConsumes<Object<ExperienceDto>>("application/json");

    info->addResponse<Object<ExperienceDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["ExperienceId"].description = "Experience Identifier";
  }
  ENDPOINT("PUT", "Experiences/{ExperienceId}", putExperience,
           PATH(Int32, ExperienceId),
           BODY_DTO(Object<ExperienceDto>, ExperienceDto))
  {
    ExperienceDto->id = ExperienceId;
    return createDtoResponse(Status::CODE_200, m_ExperienceService.updateExperience(ExperienceDto));
  }
  
  
  ENDPOINT_INFO(getExperienceById) {
    info->summary = "Get one Experience by ExperienceId";

    info->addResponse<Object<ExperienceDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["ExperienceId"].description = "Experience Identifier";
  }
  ENDPOINT("GET", "Experiences/{ExperienceId}", getExperienceById,
           PATH(Int32, ExperienceId))
  {
    return createDtoResponse(Status::CODE_200, m_ExperienceService.getExperienceById(ExperienceId));
  }
  
  
  ENDPOINT_INFO(getExperiences) {
    info->summary = "get all stored Experiences";

    info->addResponse<oatpp::Object<ExperiencesPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "Experiences/offset/{offset}/limit/{limit}", getExperiences,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_ExperienceService.getAllExperiences(offset, limit));
  }
  
  
  ENDPOINT_INFO(deleteExperience) {
    info->summary = "Delete Experience by ExperienceId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["ExperienceId"].description = "Experience Identifier";
  }
  ENDPOINT("DELETE", "Experiences/{ExperienceId}", deleteExperience,
           PATH(Int32, ExperienceId))
  {
    return createDtoResponse(Status::CODE_200, m_ExperienceService.deleteExperienceById(ExperienceId));
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* ExperienceController_hpp */