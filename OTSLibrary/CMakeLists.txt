project(OTSLibrary)
add_library(OTSLibrary SHARED
        src/types/Uuid.cpp
        src/types/Printable.cpp
        include/OTSLibrary/Types/AnyType.h
        include/OTSLibrary/Types/Printable.h
        include/OTSLibrary/Types/Uuid.h
        include/OTSLibrary/Apps/App.h
        )
target_include_directories(OTSLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)