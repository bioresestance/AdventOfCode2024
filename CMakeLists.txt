cmake_minimum_required(VERSION 3.25)
project(AoC2024 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and install GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Add the common library
add_subdirectory(common)

# Find all subdirectories matching the pattern "day-xx"
file(GLOB DAY_DIRECTORIES RELATIVE ${CMAKE_SOURCE_DIR} "day-[0-9][0-9]")

# Add each found subdirectory
foreach(DAY_DIR ${DAY_DIRECTORIES})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${DAY_DIR})
        add_subdirectory(${DAY_DIR})
    endif()
endforeach()
