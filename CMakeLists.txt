cmake_minimum_required(VERSION 3.20)
project(crud)

set(CMAKE_CXX_STANDARD 17)

add_library(crud-lib
        src/controller/StaticController.hpp
        src/controller/SkillController.hpp
        src/controller/EducationController.hpp
        src/controller/ExperienceController.hpp
        src/controller/Personal_infoController.hpp
        src/db/SkillDb.hpp
        src/db/EducationDb.hpp
        src/db/ExperienceDb.hpp
        src/db/Personal_infoDb.hpp
        src/dto/PageDto.hpp
        src/dto/StatusDto.hpp
        src/dto/SkillDto.hpp
        src/dto/EducationDto.hpp
        src/dto/ExperienceDto.hpp
        src/dto/Personal_infoDto.hpp
        src/service/SkillService.cpp
        src/service/SkillService.hpp
        src/service/EducationService.cpp
        src/service/EducationService.hpp
        src/service/ExperienceService.cpp
        src/service/ExperienceService.hpp
        src/service/Personal_infoService.cpp
        src/service/Personal_infoService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp)

## include directories

target_include_directories(crud-lib PUBLIC src)

## link libs

find_package(oatpp          1.4.0 REQUIRED)
find_package(oatpp-swagger  1.4.0 REQUIRED)
find_package(oatpp-sqlite   1.4.0 REQUIRED)

target_link_libraries(crud-lib
        # Oat++
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

# If CMake can't find SQLite3:
#
# 1. Make sure that you've built oatpp-sqlite with -DOATPP_SQLITE_AMALGAMATION=ON flag
# 2. If you are not willing to use SQLite amalgamation then uncomment the following lines:
#
#find_package(SQLite3 REQUIRED)
#
#target_link_libraries(crud-lib
#        PUBLIC SQLite::SQLite3
#)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(crud-exe src/App.cpp)
target_link_libraries(crud-exe crud-lib)

#add_executable(crud-test
#        test/tests.cpp
#        test/app/TestClient.hpp
#        test/app/TestDatabaseComponent.hpp
#        test/app/TestComponent.hpp
#        test/UserControllerTest.hpp
#        test/UserControllerTest.cpp)
#target_link_libraries(crud-test crud-lib)

#enable_testing()
#add_test(project-tests crud-test)

## CPack configuration

include(CPack)

set(CPACK_PACKAGE_NAME "crud")
set(CPACK_PACKAGE_VENDOR "Your Company")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple CRUD application")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
endif()

if(UNIX)
    set(CPACK_GENERATOR "TGZ")
elseif(WIN32)
    set(CPACK_GENERATOR "ZIP")
endif()

# Optional: Additional settings for RPM or DEB packages
#set(CPACK_RPM_PACKAGE_REQUIRES "oatpp")
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "oatpp")

# Add additional package contents (e.g., config files, documentation)
install(TARGETS crud-exe DESTINATION bin)
install(DIRECTORY src/ DESTINATION include/crud FILES_MATCHING PATTERN "*.hpp")

# Finalize CPack
include(CPack)

# Set CPack variables
set(CPACK_PACKAGE_NAME "YourProjectName")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Your Project Description")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

include(CPack)

