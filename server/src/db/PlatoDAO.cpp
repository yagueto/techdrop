
#include "PlatoDAO.h"

#include <iostream>

bd &PlatoDAO:: db = bd::get_instance();

PlatoDAO::PlatoDAO() = default;

void PlatoDAO::insert(const Plato &plato) {
    string sql = "INSERT INTO Plato(nombre, descripcion, precio, disponible) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt = db.preparar_consulta(sql);

    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Error executing statement\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_text(stmt,1,plato.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt,1,plato.getDescp().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt,1,plato.getPrecio());
    sqlite3_bind_int(stmt,1,plato.getDisponibilidad());

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}
void PlatoDAO::del(const Plato &plato) {
    sqlite3_stmt* stmt;

    string sql = "DELETE FROM Plato WHERE ID = ?;";

    int result = db.execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_int(stmt, 1, plato.getId());

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }


    sqlite3_finalize(stmt);
}
std::vector<Plato> PlatoDAO::getPlatos() {
    std::vector<Plato> platos;
    const std::string sql = "SELECT * FROM Plato";
    sqlite3_stmt *stmt = nullptr;


    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        cout << "Error preparando consulta" << endl;
        return platos;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id=sqlite3_column_int(stmt, 0);
        std::string nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string descripcion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        auto precio= static_cast<float>(sqlite3_column_double(stmt, 3));
        int disponible = sqlite3_column_int(stmt, 4);
        Plato paltoTemp(id,nombre,descripcion,precio,disponible);
        platos.push_back(paltoTemp);
    }
    sqlite3_finalize(stmt);
    return platos;
}
Plato PlatoDAO::get_plato_por_id(int id) {
    sqlite3_stmt *stmt = nullptr;
    std::string sql = "SELECT * FROM Plato WHERE ID=?";

    int result =db.execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        cout << "Error preparando consulta" << endl;
        return {};
    }
    sqlite3_bind_int(stmt,1,id);
    Plato p;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
        std::string descripcion = reinterpret_cast<const char*>(sqlite3_column_text(stmt,2));
        auto precio = static_cast<float>(sqlite3_column_double(stmt, 3));
        int disponible = sqlite3_column_int(stmt,4);

        p = Plato(id,nombre,descripcion,precio,disponible);
    }
    sqlite3_finalize(stmt);
    return p;
}