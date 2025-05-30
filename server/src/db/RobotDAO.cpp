#include "RobotDAO.h"
#include "sqlite3.h"
#include "bd.h"

RobotDAO::RobotDAO() {
    RobotDAO::db = bd::get_instance();
}

void RobotDAO::insert(const Robot& robot)
{
    string sql = "INSERT INTO Robot (id, nombre, estado, pedido_actual) VALUES (NULL, ?, ?, ?);";

    sqlite3_stmt* stmt = db.preparar_consulta(sql);

    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Error executing INSERT\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_int(stmt, 1, robot.getId());
    sqlite3_bind_text(stmt, 2, robot.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, robot.getEstado());
    sqlite3_bind_int(stmt, 4, robot.getPedidoActual());


    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing INSERT\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}

void RobotDAO::update(const Robot& robot)
{
    const char* sql = "UPDATE Robot SET nombre = ?, estado = ?, pedido_actual = ? WHERE id = ?;";
    sqlite3_stmt* stmt = db.preparar_consulta(sql);

    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Error executing UPDATE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_text(stmt, 1, robot.getNombre().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, robot.getEstado());
    sqlite3_bind_int(stmt, 3, robot.getPedidoActual());
    sqlite3_bind_int(stmt, 4, robot.getId());

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing UPDATE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}

void RobotDAO::del(const Robot &robot) {
    sqlite3_stmt* stmt;

    string sql = "DELETE FROM Robot WHERE id = ?;";

    int result = db.execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_int(stmt, 1, robot.getId());

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }


    sqlite3_finalize(stmt);
}

Robot* RobotDAO::select(const Robot& robot)
{
    sqlite3_stmt* stmt;
    std::string sql = "SELECT id, nombre, estado, pedido_actual FROM Robot LIMIT 1;";
    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        printf("Error ejecutando SELECT\n");
        return nullptr;
    }

    Robot* usuario = nullptr;
    if ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int estado = sqlite3_column_int(stmt, 2);
        int pedido_actual = sqlite3_column_int(stmt, 3);
        usuario = new Robot(id, nombre, estado, pedido_actual);
    }

    if (result != SQLITE_ROW && result != SQLITE_DONE) {
        cout << "Error iterando sobre los resultados" << endl;
    }

    sqlite3_finalize(stmt);
    return usuario;
}


