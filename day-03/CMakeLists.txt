enable_testing()
add_executable(day-3 main.cpp)
target_link_libraries(day-3 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-3 PRIVATE ${SOURCES})
target_include_directories(day-3 PRIVATE "src")


include(GoogleTest)
gtest_discover_tests(day-3)