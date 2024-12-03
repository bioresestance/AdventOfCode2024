include(GoogleTest)
enable_testing()
add_executable(day-2 main.cpp)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-2 PRIVATE ${SOURCES})
target_include_directories(day-2 PRIVATE "src")

target_link_libraries(day-2 GTest::gtest_main Common tabulate)

gtest_discover_tests(day-2)