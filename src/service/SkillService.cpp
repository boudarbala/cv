
#include "SkillService.hpp"

oatpp::Object<SkillDto> SkillService::createSkill(const oatpp::Object<SkillDto>& dto) {

  auto dbResult = m_database->createSkill(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto SkillId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getSkillById((v_int32) SkillId);

}

oatpp::Object<SkillDto> SkillService::updateSkill(const oatpp::Object<SkillDto>& dto) {

  auto dbResult = m_database->updateSkill(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getSkillById(dto->id);

}

oatpp::Object<SkillDto> SkillService::getSkillById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getSkillById(id, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Skill not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<SkillDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<SkillDto>>> SkillService::getAllSkills(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllSkills(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<SkillDto>>>();

  auto page = PageDto<oatpp::Object<SkillDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> SkillService::deleteSkillById(const oatpp::Int32& SkillId) {
  auto dbResult = m_database->deleteSkillById(SkillId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Skill was successfully deleted";
  return status;
}