enable_testing()
add_executable(day-13 main.cpp)
target_link_libraries(day-13 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-13 PRIVATE ${SOURCES})
target_include_directories(day-13 PRIVATE "src")