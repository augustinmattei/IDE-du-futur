cmake_minimum_required(VERSION 3.10)

set(BINARY StumperIDE)

file(GLOB_RECURSE src "*.cpp")
add_executable(${BINARY} ${src})

target_include_directories(${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${BINARY}
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)