enable_testing()
add_executable(day-1 main.cpp)

target_link_libraries(day-1 GTest::gtest_main Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-1 PRIVATE ${SOURCES})
target_include_directories(day-1 PRIVATE "src")


include(GoogleTest)
gtest_discover_tests(day-1)