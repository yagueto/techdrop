cmake_minimum_required(VERSION 3.30)
project(techdrop C)

set(CMAKE_C_STANDARD 11)

include_directories(src lib)

add_executable(techdrop
        src/main.c
        src/utils.c
        lib/sqlite3.c
        src/estadisticas.c
        src/models/usuario.c
        src/models/robot.c
        src/menu.c
        src/screens/gestion_menu.c
        src/screens/gestion_usuario.c
        src/db/bd_new.c
        src/db/bd_new.h
        src/db/bd_plato.c
        src/db/bd_plato.h
        src/models/plato.c
        src/models/plato.h
        src/models/pedido.c
        src/models/pedido.h
        src/db/bd_usuario.h
        src/db/bd_usuario.c
        src/db/bd_robot.c
        src/db/bd_robot.h
        src/screens/gestion_robot.c
        src/screens/gestion_robot.h
        src/db/bd_pedido.c
        src/db/bd_pedido.h
        src/db/bd_estadisticas.c
        src/db/bd_estadisticas.h
        src/screens/gestion_estadisticas.h
        src/screens/gestion_estadisticas.c
        src/config.c
        src/config.h
)
