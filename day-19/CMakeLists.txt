enable_testing()
add_executable(day-19 main.cpp)
target_link_libraries(day-19 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-19 PRIVATE ${SOURCES})
target_include_directories(day-19 PRIVATE "src")