cmake_minimum_required(VERSION 3.30)
project(client CXX)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
        ${SRC_DIR}/main.cpp
        src/Menu.cpp
        src/Menu.h

)

# Define executable
add_executable(client ${SOURCES})

# Use modern target-based includes
target_include_directories(client PRIVATE
        ${SRC_DIR}
        ${LIB_DIR}
)
target_link_libraries(client PRIVATE common ws2_32)
