project(NamePrinterApp)

set(FILES NamePrinterApp.cpp NamePrinterApp.h)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_library(NamePrinterApp SHARED ${FILES})
target_link_libraries(NamePrinterApp PRIVATE OTSLibrary VersionControl Boost::boost fmt::fmt)