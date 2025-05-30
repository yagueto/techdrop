#include "MenuUsuario.h"

MenuUsuario::MenuUsuario(const Socket &socket)
    : Menu(socket, "CONFIGURACION USUARIO") {
    anadirOpcion("Cambiar username");
    anadirOpcion("Cambiar contraseña");
    anadirOpcion("Borrar cuenta");
}

void MenuUsuario::gestionarOpcion(const int opcion)
{
    switch (opcion)
    {
    case 1:
        {
            string username_nuevo;
            cout <<"Nuevo username: ";
            getline(cin, username_nuevo);

            Message mensaje = Message(UPDATE_USERNAME, REQUEST);
            mensaje.add_param(usuario.getDni());
            mensaje.add_param(username_nuevo);
            server_socket.send_message(mensaje.serialize());
            break;
        }

    case 2:
        {
            string password_nueva;
            cout << "Nueva contraseña: ";
            getline(cin, password_nueva);

            Message mensaje = Message(UPDATE_PASSWORD, REQUEST);
            mensaje.add_param(usuario.getDni());
            mensaje.add_param(password_nueva);
            server_socket.send_message(mensaje.serialize());
            cout << server_socket.receive_message().message << endl;
            break;
        }

    case 3:
        {
            Message mensaje = Message(DELETE_USER, REQUEST);
            mensaje.add_param(usuario.getDni());
            server_socket.send_message(mensaje.serialize());
            break;
        }

    default:
        cout << "Opcion no valida." << endl;
        return;
    }

    Socket::MessageResult result = server_socket.receive_message();
    if (result.status == Socket::MessageResult::SUCESS) {
        string rRaw = result.message;
        Message respuesta = Message::deserialize(rRaw);
        if (respuesta.get_params().at(0) == "200") {
            cout << "Operación completada correctamente." << endl;
        } else {
            cout << "Error en la operación." << endl;
        }
    } else {
        cout << "Error al recibir mensaje del servidor." << endl;
    }
}

