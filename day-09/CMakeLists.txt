enable_testing()
add_executable(day-9 main.cpp)
target_link_libraries(day-9 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-9 PRIVATE ${SOURCES})
target_include_directories(day-9 PRIVATE "src")


# include(GoogleTest)
# gtest_discover_tests(day-9)