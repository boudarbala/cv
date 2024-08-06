
#ifndef CRUD_EducationSERVICE_HPP
#define CRUD_EducationSERVICE_HPP

#include "db/EducationDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/macro/component.hpp"

class EducationService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<EducationDb>, m_database); // Inject database component
public:

  oatpp::Object<EducationDto> createEducation(const oatpp::Object<EducationDto>& dto);
  oatpp::Object<EducationDto> updateEducation(const oatpp::Object<EducationDto>& dto);
  oatpp::Object<EducationDto> getEducationById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
  oatpp::Object<PageDto<oatpp::Object<EducationDto>>> getAllEducations(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteEducationById(const oatpp::Int32& id);

};

#endif //CRUD_EducationSERVICE_HPP