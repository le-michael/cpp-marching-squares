find_package(SFML COMPONENTS graphics system window REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "noise.hpp" "grid.h" "grid.cpp" "cell.h" "cell.cpp")

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window)

