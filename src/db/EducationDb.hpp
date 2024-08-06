
#ifndef CRUD_EducationDB_HPP
#define CRUD_EducationDB_HPP

#include "dto/EducationDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include "oatpp/base/Log.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * EducationDb client definitions.
 */
class EducationDb : public oatpp::orm::DbClient {
public:

  EducationDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGd("EducationDb", "Migration - OK. Version={}.", version);

  }

  QUERY(createEducation,
        "INSERT INTO AppEducation"
        "(Educationname, email, password, role) VALUES "
        "(:Education.Educationname, :Education.email, :Education.password, :Education.role);",
        PARAM(oatpp::Object<EducationDto>, Education))

  QUERY(updateEducation,
        "UPDATE AppEducation "
        "SET "
        " Educationname=:Education.Educationname, "
        " email=:Education.email, "
        " password=:Education.password, "
        " role=:Education.role "
        "WHERE "
        " id=:Education.id;",
        PARAM(oatpp::Object<EducationDto>, Education))

  QUERY(getEducationById,
        "SELECT * FROM AppEducation WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllEducations,
        "SELECT * FROM AppEducation LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteEducationById,
        "DELETE FROM AppEducation WHERE id=:id;",
        PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_EducationDB_HPP