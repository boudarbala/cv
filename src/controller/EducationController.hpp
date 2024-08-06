
#ifndef EducationController_hpp
#define EducationController_hpp

#include "service/EducationService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Education REST controller.
 */
class EducationController : public oatpp::web::server::api::ApiController {
public:
  EducationController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
private:
  EducationService m_EducationService; // Create Education service.
public:

  static std::shared_ptr<EducationController> createShared(
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
  ){
    return std::make_shared<EducationController>(apiContentMappers);
  }
  
  ENDPOINT_INFO(createEducation) {
    info->summary = "Create new Education";

    info->addConsumes<Object<EducationDto>>("application/json");

    info->addResponse<Object<EducationDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "Educations", createEducation,
           BODY_DTO(Object<EducationDto>, educationDto))
  {
    return createDtoResponse(Status::CODE_200, m_EducationService.createEducation(educationDto));
  }
  
  
  ENDPOINT_INFO(putEducation) {
    info->summary = "Update Education by EducationId";

    info->addConsumes<Object<EducationDto>>("application/json");

    info->addResponse<Object<EducationDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["EducationId"].description = "Education Identifier";
  }
  ENDPOINT("PUT", "Educations/{EducationId}", putEducation,
           PATH(Int32, educationId),
           BODY_DTO(Object<EducationDto>, educationDto))
  {
    educationDto->id = educationId;
    return createDtoResponse(Status::CODE_200, m_EducationService.updateEducation(educationDto));
  }
  
  
  ENDPOINT_INFO(getEducationById) {
    info->summary = "Get one Education by EducationId";

    info->addResponse<Object<EducationDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["EducationId"].description = "Education Identifier";
  }
  ENDPOINT("GET", "Educations/{EducationId}", getEducationById,
           PATH(Int32, educationId))
  {
    return createDtoResponse(Status::CODE_200, m_EducationService.getEducationById(educationId));
  }
  
  
  ENDPOINT_INFO(getEducations) {
    info->summary = "get all stored Educations";

    info->addResponse<oatpp::Object<EducationsPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "Educations/offset/{offset}/limit/{limit}", getEducations,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_EducationService.getAllEducations(offset, limit));
  }
  
  
  ENDPOINT_INFO(deleteEducation) {
    info->summary = "Delete Education by EducationId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["EducationId"].description = "Education Identifier";
  }
  ENDPOINT("DELETE", "Educations/{EducationId}", deleteEducation,
           PATH(Int32, educationId))
  {
    return createDtoResponse(Status::CODE_200, m_EducationService.deleteEducationById(educationId));
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* EducationController_hpp */