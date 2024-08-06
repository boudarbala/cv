
#ifndef CRUD_SkillDB_HPP
#define CRUD_SkillDB_HPP

#include "dto/SkillDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include "oatpp/base/Log.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * SkillDb client definitions.
 */
class SkillDb : public oatpp::orm::DbClient {
public:

  SkillDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/db.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGd("SkillDb", "Migration - OK. Version={}.", version);

  }

  QUERY(createSkill,
        "INSERT INTO AppSkill"
        "(Skillname, email, password, role) VALUES "
        "(:Skill.Skillname, :Skill.email, :Skill.password, :Skill.role);",
        PARAM(oatpp::Object<SkillDto>, Skill))

  QUERY(updateSkill,
        "UPDATE AppSkill "
        "SET "
        " Skillname=:Skill.Skillname, "
        " email=:Skill.email, "
        " password=:Skill.password, "
        " role=:Skill.role "
        "WHERE "
        " id=:Skill.id;",
        PARAM(oatpp::Object<SkillDto>, Skill))

  QUERY(getSkillById,
        "SELECT * FROM AppSkill WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllSkills,
        "SELECT * FROM AppSkill LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteSkillById,
        "DELETE FROM AppSkill WHERE id=:id;",
        PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_SkillDB_HPP