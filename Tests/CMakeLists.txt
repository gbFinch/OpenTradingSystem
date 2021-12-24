cmake_minimum_required(VERSION 3.16)
project(Tests)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(FILE_SET
        tests.cpp
        TypesTests.cpp
        )

add_executable(Tests ${FILE_SET})
target_link_libraries(Tests PRIVATE OTSLibrary VersionControl fmt::fmt Boost::boost Boost::filesystem range-v3 nlohmann_json pugixml ${CMAKE_DL_LIBS} Catch2::Catch2 Catch2::Catch2WithMain)