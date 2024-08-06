
#ifndef CRUD_Personal_infoDB_HPP
#define CRUD_Personal_infoDB_HPP

#include "dto/Personal_infoDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include "oatpp/base/Log.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * Personal_infoDb client definitions.
 */
class Personal_infoDb : public oatpp::orm::DbClient {
public:

  Personal_infoDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/db.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGd("Personal_infoDb", "Migration - OK. Version={}.", version);

  }

  QUERY(createPersonal_info,
        "INSERT INTO AppPersonal_info"
        "(Personal_infoname, email, password, role) VALUES "
        "(:Personal_info.Personal_infoname, :Personal_info.email, :Personal_info.password, :Personal_info.role);",
        PARAM(oatpp::Object<Personal_infoDto>, Personal_info))

  QUERY(updatePersonal_info,
        "UPDATE AppPersonal_info "
        "SET "
        " Personal_infoname=:Personal_info.Personal_infoname, "
        " email=:Personal_info.email, "
        " password=:Personal_info.password, "
        " role=:Personal_info.role "
        "WHERE "
        " id=:Personal_info.id;",
        PARAM(oatpp::Object<Personal_infoDto>, Personal_info))

  QUERY(getPersonal_infoById,
        "SELECT * FROM AppPersonal_info WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllPersonal_infos,
        "SELECT * FROM AppPersonal_info LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deletePersonal_infoById,
        "DELETE FROM AppPersonal_info WHERE id=:id;",
        PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_Personal_infoDB_HPP