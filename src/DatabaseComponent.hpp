
#ifndef CRUD_DATABASECOMPONENT_HPP
#define CRUD_DATABASECOMPONENT_HPP

#include "db/EducationDb.hpp"
#include "db/ExperienceDb.hpp"
#include "db/Personal_infoDb.hpp"
#include "db/SkillDb.hpp"

class DatabaseComponent {
public:
    
  /**
   * Create database connection provider component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([] {

    /* Create database-specific ConnectionProvider */
    auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

    /* Create database-specific ConnectionPool */
    return oatpp::sqlite::ConnectionPool::createShared(connectionProvider,
                                                       10 /* max-connections */,
                                                       std::chrono::seconds(5) /* connection TTL */);

  }());

  /**
   * Create database Experience
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<ExperienceDb>, experienceDb)([] {

    /* Get database ConnectionProvider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

    /* Create MyClient database client */
    return std::make_shared<ExperienceDb>(executor);

  }());

  
  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<EducationDb>, educationDb)([] {

    /* Get database ConnectionProvider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

    /* Create MyClient database client */
    return std::make_shared<EducationDb>(executor);

  }());


  
  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<Personal_infoDb>, personal_infoDb)([] {

    /* Get database ConnectionProvider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

    /* Create MyClient database client */
    return std::make_shared<Personal_infoDb>(executor);

  }());

  
  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<SkillDb>, skillDb)([] {

    /* Get database ConnectionProvider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

    /* Create MyClient database client */
    return std::make_shared<SkillDb>(executor);

  }());

};

#endif //CRUD_DATABASECOMPONENT_HPP