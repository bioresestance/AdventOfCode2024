enable_testing()
add_executable(day-15 main.cpp)
target_link_libraries(day-15 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-15 PRIVATE ${SOURCES})
target_include_directories(day-15 PRIVATE "src")