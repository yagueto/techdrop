cmake_minimum_required(VERSION 3.30)
project(techdrop C)

set(CMAKE_C_STANDARD 11)

add_executable(techdrop
        src/main.c
        src/utils.c
        lib/sqlite3.c
        src/bd.c
        src/estadisticas.c
        src/estructuras/estructuras.c
        src/estructuras/usuario.c
        src/estructuras/robot.c
        src/estructuras/robot.h
        src/menu.c
        src/menu.h
        src/screens/gestion_menu.c
        src/screens/gestion_menu.h
)
