
#ifndef Personal_infoController_hpp
#define Personal_infoController_hpp

#include "service/Personal_infoService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Personal_info REST controller.
 */
class Personal_infoController : public oatpp::web::server::api::ApiController {
public:
  Personal_infoController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
private:
  Personal_infoService m_Personal_infoService; // Create Personal_info service.
public:

  static std::shared_ptr<Personal_infoController> createShared(
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
  ){
    return std::make_shared<Personal_infoController>(apiContentMappers);
  }
  
  ENDPOINT_INFO(createPersonal_info) {
    info->summary = "Create new Personal_info";

    info->addConsumes<Object<Personal_infoDto>>("application/json");

    info->addResponse<Object<Personal_infoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "Personal_infos", createPersonal_info,
           BODY_DTO(Object<Personal_infoDto>, Personal_infoDto))
  {
    return createDtoResponse(Status::CODE_200, m_Personal_infoService.createPersonal_info(Personal_infoDto));
  }
  
  
  ENDPOINT_INFO(putPersonal_info) {
    info->summary = "Update Personal_info by Personal_infoId";

    info->addConsumes<Object<Personal_infoDto>>("application/json");

    info->addResponse<Object<Personal_infoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["Personal_infoId"].description = "Personal_info Identifier";
  }
  ENDPOINT("PUT", "Personal_infos/{Personal_infoId}", putPersonal_info,
           PATH(Int32, Personal_infoId),
           BODY_DTO(Object<Personal_infoDto>, Personal_infoDto))
  {
    Personal_infoDto->id = Personal_infoId;
    return createDtoResponse(Status::CODE_200, m_Personal_infoService.updatePersonal_info(Personal_infoDto));
  }
  
  
  ENDPOINT_INFO(getPersonal_infoById) {
    info->summary = "Get one Personal_info by Personal_infoId";

    info->addResponse<Object<Personal_infoDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["Personal_infoId"].description = "Personal_info Identifier";
  }
  ENDPOINT("GET", "Personal_infos/{Personal_infoId}", getPersonal_infoById,
           PATH(Int32, Personal_infoId))
  {
    return createDtoResponse(Status::CODE_200, m_Personal_infoService.getPersonal_infoById(Personal_infoId));
  }
  
  
  ENDPOINT_INFO(getPersonal_infos) {
    info->summary = "get all stored Personal_infos";

    info->addResponse<oatpp::Object<Personal_infosPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "Personal_infos/offset/{offset}/limit/{limit}", getPersonal_infos,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_Personal_infoService.getAllPersonal_infos(offset, limit));
  }
  
  
  ENDPOINT_INFO(deletePersonal_info) {
    info->summary = "Delete Personal_info by Personal_infoId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["Personal_infoId"].description = "Personal_info Identifier";
  }
  ENDPOINT("DELETE", "Personal_infos/{Personal_infoId}", deletePersonal_info,
           PATH(Int32, Personal_infoId))
  {
    return createDtoResponse(Status::CODE_200, m_Personal_infoService.deletePersonal_infoById(Personal_infoId));
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* Personal_infoController_hpp */