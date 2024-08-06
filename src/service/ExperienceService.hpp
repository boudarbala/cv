
#ifndef CRUD_ExperienceSERVICE_HPP
#define CRUD_ExperienceSERVICE_HPP

#include "db/ExperienceDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/macro/component.hpp"

class ExperienceService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<ExperienceDb>, m_database); // Inject database component
public:

  oatpp::Object<ExperienceDto> createExperience(const oatpp::Object<ExperienceDto>& dto);
  oatpp::Object<ExperienceDto> updateExperience(const oatpp::Object<ExperienceDto>& dto);
  oatpp::Object<ExperienceDto> getExperienceById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
  oatpp::Object<PageDto<oatpp::Object<ExperienceDto>>> getAllExperiences(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteExperienceById(const oatpp::Int32& id);

};

#endif //CRUD_ExperienceSERVICE_HPP