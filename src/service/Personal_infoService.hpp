
#ifndef CRUD_Personal_infoSERVICE_HPP
#define CRUD_Personal_infoSERVICE_HPP

#include "db/Personal_infoDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/macro/component.hpp"

class Personal_infoService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<Personal_infoDb>, m_database); // Inject database component
public:

  oatpp::Object<Personal_infoDto> createPersonal_info(const oatpp::Object<Personal_infoDto>& dto);
  oatpp::Object<Personal_infoDto> updatePersonal_info(const oatpp::Object<Personal_infoDto>& dto);
  oatpp::Object<Personal_infoDto> getPersonal_infoById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
  oatpp::Object<PageDto<oatpp::Object<Personal_infoDto>>> getAllPersonal_infos(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deletePersonal_infoById(const oatpp::Int32& id);

};

#endif //CRUD_Personal_infoSERVICE_HPP