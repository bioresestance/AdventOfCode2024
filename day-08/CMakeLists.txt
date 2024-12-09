enable_testing()
add_executable(day-8 main.cpp)
target_link_libraries(day-8 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-8 PRIVATE ${SOURCES})
target_include_directories(day-8 PRIVATE "src")


include(GoogleTest)
gtest_discover_tests(day-8)