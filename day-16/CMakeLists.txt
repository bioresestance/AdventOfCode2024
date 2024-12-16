enable_testing()
add_executable(day-16 main.cpp)
target_link_libraries(day-16 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-16 PRIVATE ${SOURCES})
target_include_directories(day-16 PRIVATE "src")