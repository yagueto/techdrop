//
// Created by termi on 30/05/2025.
//

#include "PedidoDAO.h"

bd &PedidoDAO::db = bd::get_instance();

PedidoDAO::PedidoDAO() {
}

void PedidoDAO::insert(Pedido &pedido) {
    sqlite3_stmt* stmt;
    std::string sql = "INSERT INTO Pedido (id_usuario, direccion, fecha, estado) VALUES (?, ?, ?, ?);";
    int result = db.execute_query(sql, &stmt);
    if (result != 0) {
        std::cout << "Error preparando la consulta" << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, pedido.getIdUsuario());
    sqlite3_bind_text(stmt, 2, pedido.getDireccion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, pedido.getFecha());
    sqlite3_bind_int(stmt, 4, pedido.getEstado());
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cout << "Error ejecutando la inserción" << std::endl;
    } else {
        std::cout << "Pedido insertado correctamente." << std::endl;
    }
    sqlite3_finalize(stmt);
}

void PedidoDAO::del(Pedido &pedido) {
    sqlite3_stmt* stmt;
    std::string sql = "DELETE FROM Pedido WHERE id_pedido = ?;";
    int result = db.execute_query(sql, &stmt);
    if (result != 0) {
        std::cout << "Error preparando la consulta" << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, pedido.getIdPedido());
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cout << "Error ejecutando la eliminación" << std::endl;
    } else {
        std::cout << "Pedido eliminado correctamente." << std::endl;
    }
    sqlite3_finalize(stmt);
}

Pedido * PedidoDAO::select(Pedido &pedido) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT id_pedido, id_usuario, direccion, fecha, estado FROM Pedido WHERE id_pedido = ?;";
    int result = db.execute_query(sql, &stmt);
    if (result != 0) {
        std::cout << "Error preparando la consulta" << std::endl;
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, pedido.getIdPedido());

    result = sqlite3_step(stmt);
    Pedido* p = nullptr;
    if (result == SQLITE_ROW) {
        int id_pedido = sqlite3_column_int(stmt, 0);
        int id_usuario = sqlite3_column_int(stmt, 1);
        std::string direccion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string fecha_str = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        time_t fecha = std::stol(fecha_str);
        int estado = sqlite3_column_int(stmt, 4);

        p = new Pedido(id_pedido, id_usuario, direccion, fecha, estado);
    } else {
        std::cout << "No existe este pedido" << std::endl;
    }

    sqlite3_finalize(stmt);
    return p;
}
