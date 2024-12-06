enable_testing()
add_executable(day-5 main.cpp)
target_link_libraries(day-5 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-5 PRIVATE ${SOURCES})
target_include_directories(day-5 PRIVATE "src")


include(GoogleTest)
gtest_discover_tests(day-5)