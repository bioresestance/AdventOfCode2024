enable_testing()
add_executable(day-7 main.cpp)
target_link_libraries(day-7 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-7 PRIVATE ${SOURCES})
target_include_directories(day-7 PRIVATE "src")


include(GoogleTest)
gtest_discover_tests(day-7)