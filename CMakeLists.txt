cmake_minimum_required(VERSION 3.16)
project(OpenTradingSystem)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(OTSLibrary)
add_subdirectory(VersionControl)
add_subdirectory(Apps)
add_subdirectory(OTSCore)
add_subdirectory(Tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenTradingSystem main.cpp)
target_link_libraries(OpenTradingSystem PRIVATE OTSLibrary VersionControl fmt::fmt Boost::boost range-v3 nlohmann_json)