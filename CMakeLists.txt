
cmake_minimum_required(VERSION 3.20)
project(Project2DSA)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake where SFML is installed
#set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")
# Path to SFML (adjust if different)
set(SFML_DIR "C:/SFML-3.0.2-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.2/lib/cmake/SFML")

# Find the required SFML 3 modules
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(Project2DSA
        main.cpp
        dijkstra.cpp
        dijkstra.h
        display.cpp
        display.h
        Star.cpp
        Star.h
        StarGroup.cpp
        StarGroup.h
        )

# Link to the SFML 3 targets
target_link_libraries(Project2DSA PRIVATE SFML::Graphics SFML::Window SFML::System)
