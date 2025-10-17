cmake_minimum_required(VERSION 3.15)
project(GreenhouseSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Include header directory
include_directories(include)

# Collect all .cpp files
file(GLOB SRC_FILES src/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link SFML
target_link_libraries(${PROJECT_NAME}
    PRIVATE sfml-graphics sfml-window sfml-system
)
