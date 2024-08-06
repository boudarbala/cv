
#include "ExperienceService.hpp"

oatpp::Object<ExperienceDto> ExperienceService::createExperience(const oatpp::Object<ExperienceDto>& dto) {

  auto dbResult = m_database->createExperience(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto ExperienceId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getExperienceById((v_int32) ExperienceId);

}

oatpp::Object<ExperienceDto> ExperienceService::updateExperience(const oatpp::Object<ExperienceDto>& dto) {

  auto dbResult = m_database->updateExperience(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getExperienceById(dto->id);

}

oatpp::Object<ExperienceDto> ExperienceService::getExperienceById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getExperienceById(id, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Experience not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ExperienceDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<ExperienceDto>>> ExperienceService::getAllExperiences(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllExperiences(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ExperienceDto>>>();

  auto page = PageDto<oatpp::Object<ExperienceDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> ExperienceService::deleteExperienceById(const oatpp::Int32& ExperienceId) {
  auto dbResult = m_database->deleteExperienceById(ExperienceId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Experience was successfully deleted";
  return status;
}