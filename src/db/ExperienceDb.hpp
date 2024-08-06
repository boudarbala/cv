
#ifndef CRUD_ExperienceDB_HPP
#define CRUD_ExperienceDB_HPP

#include "dto/ExperienceDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include "oatpp/base/Log.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * ExperienceDb client definitions.
 */
class ExperienceDb : public oatpp::orm::DbClient {
public:

  ExperienceDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/db.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGd("ExperienceDb", "Migration - OK. Version={}.", version);

  }

  QUERY(createExperience,
        "INSERT INTO AppExperience"
        "(Experiencename, email, password, role) VALUES "
        "(:Experience.Experiencename, :Experience.email, :Experience.password, :Experience.role);",
        PARAM(oatpp::Object<ExperienceDto>, Experience))

  QUERY(updateExperience,
        "UPDATE AppExperience "
        "SET "
        " Experiencename=:Experience.Experiencename, "
        " email=:Experience.email, "
        " password=:Experience.password, "
        " role=:Experience.role "
        "WHERE "
        " id=:Experience.id;",
        PARAM(oatpp::Object<ExperienceDto>, Experience))

  QUERY(getExperienceById,
        "SELECT * FROM AppExperience WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllExperiences,
        "SELECT * FROM AppExperience LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteExperienceById,
        "DELETE FROM AppExperience WHERE id=:id;",
        PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_ExperienceDB_HPP