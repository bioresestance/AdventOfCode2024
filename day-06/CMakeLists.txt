enable_testing()
add_executable(day-6 main.cpp)
target_link_libraries(day-6 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-6 PRIVATE ${SOURCES})
target_include_directories(day-6 PRIVATE "src")


include(GoogleTest)
# gtest_discover_tests(day-6 DISCOVERY_TIMEOUT 3600)