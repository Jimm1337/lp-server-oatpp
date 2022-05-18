# initial config
cmake_minimum_required(VERSION 3.5)
set(project_name lp-server-oatpp)
project(${project_name})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add conan package manager
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake")
    file(
         DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
         "${CMAKE_BINARY_DIR}/conan.cmake"
         TLS_VERIFY ON
    )
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# download external libs via conan
conan_cmake_run(REQUIRES
        sqlite3/3.38.5
        libgpiod/1.6.3
        oatpp/1.3.0
        oatpp-swagger/1.3.0
        oatpp-sqlite/1.3.0

        BASIC_SETUP
        CMAKE_TARGETS
        OPTIONS
        BUILD missing
        GENERATORS cmake_find_package
)

# find external libs
find_package(SQLite3 REQUIRED)
find_package(libgpiod REQUIRED)
find_package(oatpp REQUIRED)
find_package(oatpp-swagger REQUIRED)
find_package(oatpp-sqlite REQUIRED)

# add extra warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
            /permissive- /W4 /w14640 /w14242 /w14254 /w14263 /w14265
            /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547
            /w14549 /w14555 /w14619 /w14826 /w14905 /w14906 /w14928
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
            -Wall -Wextra -Wpedantic -Wshadow
            -Wnon-virtual-dtor -Wold-style-cast
            -Wcast-align -Wunused -Woverloaded-virtual
            -Wconversion -Wsign-conversion -Wmisleading-indentation
            -Wduplicated-cond -Wduplicated-branches -Wlogical-op
            -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
            -Wall -Wextra -Wpedantic -Wshadow
            -Wnon-virtual-dtor -Wold-style-cast
            -Wcast-align -Wunused -Woverloaded-virtual
            -Wconversion -Wsign-conversion -Wdouble-promotion
            -Wformat=2 -Wlifetime
    )
endif()

# Release and Debug mode
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_BUILD_TYPE Release)
endif()

# flags
if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/Od /fsanitize=address,undefined)
        add_link_options(/fsanitize=address,undefined)
    else()
       add_compile_options(-fsanitize=thread,undefined -Og -g)
       add_link_options(-fsanitize=address,undefined)
    endif()
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/O2)
    else()
        add_compile_options(-O2)
    endif()
endif()

# include src
include_directories(src)

# add main library
add_library(${project_name}-lib
        src/controller/lpController.hpp
        src/db/Database.hpp
        src/dto/DTOs.hpp
        src/macro/ResponseMacros.hpp
        src/macro/UtilityMacros.hpp
        src/service/testService.cpp
        src/service/testService.hpp
)

# link libs
target_link_libraries(${project_name}-lib
        PUBLIC SQLite::SQLite3
        PUBLIC libgpiod::gpiod
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

# add useful macros
add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${CONAN_INCLUDE_DIRS_OATPP-SWAGGER}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/sql/db.sqlite"

        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/sql/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/migration/"
)

# add main executable
add_executable(${project_name}-exe
        src/App.cpp
        src/AppComponent.hpp
)

# add test executable
add_executable(${project_name}-test
        test/app/MyApiTestClient.hpp
        test/app/TestComponent.hpp
        test/lpControllerTest.cpp
        test/lpControllerTest.hpp
        test/Tests.cpp
)

# links lib and exes
target_link_libraries(${project_name}-exe ${project_name}-lib)
target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

# system specific links
if(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()
if(WIN32)
    target_link_libraries(${project_name}-lib wsock32 ws2_32)
endif()

# set project properties
set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

# testing
enable_testing()
add_test(project-tests ${CMAKE_SOURCE_DIR}/bin/${project_name}-test)
