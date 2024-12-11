enable_testing()
add_executable(day-10 main.cpp)
target_link_libraries(day-10 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-10 PRIVATE ${SOURCES})
target_include_directories(day-10 PRIVATE "src")