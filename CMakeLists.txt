cmake_minimum_required(VERSION 4.0)
project(DSA_Project_2)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake where SFML is installed
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")

# Find the required SFML 3 modules
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(DSA_Project_2
        main.cpp
        display.h
        display.cpp)

# Link to the SFML 3 targets
target_link_libraries(DSA_Project_2 PRIVATE SFML::Graphics SFML::Window SFML::System)
