enable_testing()
add_executable(day-14 main.cpp)
target_link_libraries(day-14 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-14 PRIVATE ${SOURCES})
target_include_directories(day-14 PRIVATE "src")