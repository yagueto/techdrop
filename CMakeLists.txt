cmake_minimum_required(VERSION 3.30)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
project(techdrop)

add_subdirectory(lib)

add_subdirectory(local_admin)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(common)