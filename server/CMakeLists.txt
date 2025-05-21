cmake_minimum_required(VERSION 3.30)
project(server CXX)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
        ${SRC_DIR}/main.cpp
        src/MessageHandler.cpp
        src/MessageHandler.h
)

# Define executable
add_executable(server ${SOURCES})

target_include_directories(server PRIVATE
        ${SRC_DIR}
        ${LIB_DIR}
)

target_link_libraries(server PRIVATE sqlite3 common ws2_32)
