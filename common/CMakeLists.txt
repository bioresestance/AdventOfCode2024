# List of source files
set(SOURCES
    InputFile.cpp
    Utils.cpp
)

add_library(Common ${SOURCES})
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})