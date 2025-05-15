cmake_minimum_required(VERSION 3.30)
project(server C)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
        ${SRC_DIR}/main.cpp
        src/objects/Pedido.cpp
        src/objects/Pedido.h
        src/objects/Plato.cpp
        src/objects/Plato.h
        src/objects/Usuario.cpp
        src/objects/Usuario.h
        src/objects/Robot.cpp
        src/objects/Robot.h
)

# Define executable
add_executable(server ${SOURCES})

target_include_directories(server PRIVATE
        ${SRC_DIR}
        ${LIB_DIR}
)

target_link_libraries(server PRIVATE sqlite3)
