#include "UserDAO.h"
#include "sqlite3.h"
#include "bd.h"

bd &UserDAO::db = bd::get_instance();

UserDAO::UserDAO() = default;

void UserDAO::insert(Usuario &usuario) {
    string sql = "INSERT INTO Usuario (id, dni, username, password) VALUES (NULL, ?, ?, ?);";

    sqlite3_stmt* stmt = db.preparar_consulta(sql);

    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Error executing statement\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario.getContraseña().c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}

void UserDAO::del(Usuario &usuario) {
    sqlite3_stmt* stmt;

    string sql = "DELETE FROM Usuario WHERE dni = ?;";

    int result = db.execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return;
    }


    sqlite3_finalize(stmt);
}

Usuario UserDAO::select(Usuario &usuario) {
    sqlite3_stmt* stmt;
    Usuario user = Usuario();
    std::string sql = "SELECT dni, username, password FROM Usuario WHERE dni=?";
    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        printf("Error ejecutando SELECT\n");
        return user;
    }
    sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);
    if ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
        user.setDni(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        user.setNombre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        user.setContraseña(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    }

    if (result != SQLITE_ROW && result != SQLITE_DONE) {
        cout << "Error iterando sobre los resultados" << endl;
    }

    sqlite3_finalize(stmt);
    return user;
}

void UserDAO::update(Usuario &usuario) {
    sqlite3_stmt* stmt;
    std::string sql = "UPDATE Usuario SET username = ?, password = ? WHERE dni = ?;";

    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        cout << "Error preparando consulta" << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, usuario.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario.getContraseña().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario.getDni().c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cout << "Error actualizando usuario" << endl;
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}
