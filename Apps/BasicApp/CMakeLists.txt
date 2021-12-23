project(BasicApp)

set(FILES BasicApp.cpp BasicApp.h)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_library(BasicApp SHARED ${FILES})
target_link_libraries(BasicApp PRIVATE OTSLibrary VersionControl Boost::boost fmt::fmt)