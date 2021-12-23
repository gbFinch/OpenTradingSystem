project(OTSLibrary)
add_library(OTSLibrary SHARED
        src/types/Uuid.cpp
        src/types/Printable.cpp
        include/types/AnyType.h
        include/types/Printable.h
        include/types/Uuid.h include/Apps/App.h)
target_include_directories(OTSLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)