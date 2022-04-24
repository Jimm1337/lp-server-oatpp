# initial config
cmake_minimum_required(VERSION 3.1)
set(project_name lp-server-oatpp)
project(${project_name})
set(CMAKE_CXX_STANDARD 20)

# add extra warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# set good structure
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# include src
include_directories(src)

# add main library
add_library(${project_name}-lib
        src/controller/MyController.hpp
        src/service/testService.hpp
        src/service/testService.cpp
        src/macro/ResponseMacros.hpp
        src/macro/UtilityMacros.hpp
        src/dto/DTOs.hpp
        src/db/Database.hpp
        src/AppComponent.hpp
)

# find libs
find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger 1.3.0 REQUIRED)
find_package(oatpp-sqlite 1.3.0 REQUIRED)
find_package(SQLite3 REQUIRED)
find_library(bcm2835_lib bcm2835 REQUIRED)

# link libs
target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
        PUBLIC SQLite::SQLite3
        PUBLIC bcm2835
)

# add useful macros
add_definitions(
        ## SERVER HOST IP ADDR (CHANGE THIS)
        -DSERVER_HOST_IP="192.168.0.100"

        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/sql/db.sqlite"

        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/sql/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/migration/"
)

# find and link threads (for oatpp) if linux
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

# add main executable
add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

# add test executable
add_executable(${project_name}-test
        test/Tests.cpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        test/MyControllerTest.cpp
        test/MyControllerTest.hpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

# set project properties
set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

# testing
enable_testing()
add_test(project-tests ${CMAKE_SOURCE_DIR}/bin/${project_name}-test)
