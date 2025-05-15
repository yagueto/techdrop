cmake_minimum_required(VERSION 3.30)
project(local_admin C)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
        ${SRC_DIR}/main.c
        ${SRC_DIR}/utils.c
        ${SRC_DIR}/estadisticas.c
        ${SRC_DIR}/menu.c
        ${SRC_DIR}/config.c

        ${SRC_DIR}/models/usuario.c
        ${SRC_DIR}/models/robot.c
        ${SRC_DIR}/models/plato.c
        ${SRC_DIR}/models/pedido.c

        ${SRC_DIR}/screens/gestion_menu.c
        ${SRC_DIR}/screens/gestion_usuario.c
        ${SRC_DIR}/screens/gestion_robot.c
        ${SRC_DIR}/screens/gestion_estadisticas.c

        ${SRC_DIR}/db/bd_new.c
        ${SRC_DIR}/db/bd_plato.c
        ${SRC_DIR}/db/bd_usuario.c
        ${SRC_DIR}/db/bd_robot.c
        ${SRC_DIR}/db/bd_pedido.c
        ${SRC_DIR}/db/bd_estadisticas.c
)

# Define executable
add_executable(local_admin ${SOURCES})

# Use modern target-based includes
target_include_directories(local_admin PRIVATE
        ${SRC_DIR}
        ${LIB_DIR}
)
target_link_libraries(local_admin PRIVATE sqlite3)
