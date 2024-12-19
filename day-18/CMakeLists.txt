enable_testing()
add_executable(day-18 main.cpp)
target_link_libraries(day-18 GTest::gtest Common)

file(GLOB SOURCES "src/*.cpp")
target_sources(day-18 PRIVATE ${SOURCES})
target_include_directories(day-18 PRIVATE "src")