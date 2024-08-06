
#include "Personal_infoService.hpp"

oatpp::Object<Personal_infoDto> Personal_infoService::createPersonal_info(const oatpp::Object<Personal_infoDto>& dto) {

  auto dbResult = m_database->createPersonal_info(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto Personal_infoId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getPersonal_infoById((v_int32) Personal_infoId);

}

oatpp::Object<Personal_infoDto> Personal_infoService::updatePersonal_info(const oatpp::Object<Personal_infoDto>& dto) {

  auto dbResult = m_database->updatePersonal_info(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getPersonal_infoById(dto->id);

}

oatpp::Object<Personal_infoDto> Personal_infoService::getPersonal_infoById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getPersonal_infoById(id, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Personal_info not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<Personal_infoDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<Personal_infoDto>>> Personal_infoService::getAllPersonal_infos(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllPersonal_infos(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<Personal_infoDto>>>();

  auto page = PageDto<oatpp::Object<Personal_infoDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> Personal_infoService::deletePersonal_infoById(const oatpp::Int32& Personal_infoId) {
  auto dbResult = m_database->deletePersonal_infoById(Personal_infoId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Personal_info was successfully deleted";
  return status;
}