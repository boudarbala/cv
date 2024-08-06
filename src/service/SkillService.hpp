
#ifndef CRUD_SkillSERVICE_HPP
#define CRUD_SkillSERVICE_HPP

#include "db/SkillDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/macro/component.hpp"

class SkillService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<SkillDb>, m_database); // Inject database component
public:

  oatpp::Object<SkillDto> createSkill(const oatpp::Object<SkillDto>& dto);
  oatpp::Object<SkillDto> updateSkill(const oatpp::Object<SkillDto>& dto);
  oatpp::Object<SkillDto> getSkillById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
  oatpp::Object<PageDto<oatpp::Object<SkillDto>>> getAllSkills(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteSkillById(const oatpp::Int32& id);

};

#endif //CRUD_SkillSERVICE_HPP