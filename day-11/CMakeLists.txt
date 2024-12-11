enable_testing()
add_executable(day-11 main.cpp)
target_link_libraries(day-11 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-11 PRIVATE ${SOURCES})
target_include_directories(day-11 PRIVATE "src")