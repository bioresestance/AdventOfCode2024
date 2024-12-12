enable_testing()
add_executable(day-12 main.cpp)
target_link_libraries(day-12 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-12 PRIVATE ${SOURCES})
target_include_directories(day-12 PRIVATE "src")