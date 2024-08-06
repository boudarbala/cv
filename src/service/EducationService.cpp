
#include "EducationService.hpp"

oatpp::Object<EducationDto> EducationService::createEducation(const oatpp::Object<EducationDto>& dto) {

  auto dbResult = m_database->createEducation(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto EducationId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getEducationById((v_int32) EducationId);

}

oatpp::Object<EducationDto> EducationService::updateEducation(const oatpp::Object<EducationDto>& dto) {

  auto dbResult = m_database->updateEducation(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getEducationById(dto->id);

}

oatpp::Object<EducationDto> EducationService::getEducationById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getEducationById(id, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Education not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<EducationDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<EducationDto>>> EducationService::getAllEducations(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllEducations(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<EducationDto>>>();

  auto page = PageDto<oatpp::Object<EducationDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> EducationService::deleteEducationById(const oatpp::Int32& EducationId) {
  auto dbResult = m_database->deleteEducationById(EducationId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Education was successfully deleted";
  return status;
}