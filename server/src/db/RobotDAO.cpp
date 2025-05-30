//
// Created by naia.martin on 29/05/2025.
//

#include "RobotDAO.h"

#include <domain/Robot.h>

#include "bd.h"

bool RobotDAO::insert(const Robot& robot)
{
    const char* sql = "INSERT INTO Robot(id, nombre, estado, pedido_actual) VALUES (?,?,?,?); ";
    sqlite3_stmt* stmt = bd::get_instance().preparar_consulta(sql);

    sqlite3_bind_int(stmt, 1, robot.getId());
    sqlite3_bind_text(stmt, 2, robot.getNombre().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, robot.getEstado());
    sqlite3_bind_int(stmt, 4, robot.getPedidoActual());

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

bool RobotDAO::update(const Robot& robot)
{
    const char* sql = "UPDATE Robot SET nombre = ?, estado = ?, pedido_actual = ? WHERE id = ?;";
    sqlite3_stmt* stmt = bd::get_instance().preparar_consulta(sql);

    sqlite3_bind_text(stmt, 1, robot.getNombre().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, robot.getEstado());
    sqlite3_bind_int(stmt, 3, robot.getPedidoActual());
    sqlite3_bind_int(stmt, 4, robot.getId());

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

bool RobotDAO::del(int id) {
    const char* sql = "DELETE FROM Robot WHERE id = ?;";
    sqlite3_stmt* stmt = bd::get_instance().preparar_consulta(sql);

    sqlite3_bind_int(stmt, 1, id);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

Robot RobotDAO::select(const Robot& robot)
{
    const char* sql = "SELECT FROM Robot ";
}


