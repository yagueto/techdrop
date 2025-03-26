cmake_minimum_required(VERSION 3.30)
project(techdrop C)

set(CMAKE_C_STANDARD 11)

add_executable(techdrop src/main.c src/menus/menus.c src/menus/utils.c src/menus/menu_menus.c
        src/sqlite3.h
        src/sqlite3.c
        src/bd.c
        src/bd.h

)