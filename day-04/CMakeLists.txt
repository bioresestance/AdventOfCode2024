enable_testing()
add_executable(day-4 main.cpp)
target_link_libraries(day-4 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-4 PRIVATE ${SOURCES})
target_include_directories(day-4 PRIVATE "src")


include(GoogleTest)
gtest_discover_tests(day-4)