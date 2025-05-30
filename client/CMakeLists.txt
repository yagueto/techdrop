cmake_minimum_required(VERSION 3.30)
project(client CXX)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
        ${SRC_DIR}/main.cpp
        src/Menu.cpp
        src/Menu.h
        src/screens/MenuPrincipal.cpp
        src/screens/MenuPrincipal.h
        src/screens/MenuInicio.cpp
        src/screens/MenuInicio.h
        src/screens/MenuPedidos.cpp
        src/screens/MenuPedidos.h
        src/screens/MenuUsuario.cpp
        src/screens/MenuUsuario.h
        src/road_status.cpp
        src/road_status.h
        src/Globals.h


)

# Define executable
add_executable(client ${SOURCES})

# Use modern target-based includes
target_include_directories(client PRIVATE
        ${SRC_DIR}
        ${LIB_DIR}
)
target_link_libraries(client PRIVATE common ws2_32 rapidxml)
