enable_testing()
add_executable(day-17 main.cpp)
target_link_libraries(day-17 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-17 PRIVATE ${SOURCES})
target_include_directories(day-17 PRIVATE "src")