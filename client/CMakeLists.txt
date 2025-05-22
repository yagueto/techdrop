cmake_minimum_required(VERSION 3.30)
project(client CXX)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
        ${SRC_DIR}/main.cpp
        src/Menu.cpp
        src/Menu.h
        src/Handler.cpp
        src/Handler.h
        src/screens/Gestionar_logIn.cpp
        src/screens/Gestionar_logIn.h
        src/screens/Gestionar_inicio.cpp
        src/screens/Gestionar_inicio.h
        src/screens/Gestionar_pedidos.cpp
        src/screens/Gestionar_pedidos.h
        src/screens/Gestionar_usuarios.cpp
        src/screens/Gestionar_usuarios.h
        src/screens/Gestionar_mainMenu.cpp
        src/screens/Gestionar_mainMenu.h
        src/screens/Gestionar_registro.cpp
        src/screens/Gestionar_registro.h
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
