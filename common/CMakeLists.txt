project(common CXX)

add_library(common STATIC
        domain/Pedido.cpp
        domain/Plato.cpp
        domain/Robot.cpp
        domain/Usuario.cpp
        Protocol.h
        Socket.cpp
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
