#include "UserDAO.h"
#include "bd.h"
#include "sqlite3.h"
#include <iostream>
bd &UserDAO::db = bd::get_instance();

UserDAO::UserDAO() = default;

void UserDAO::insert(Usuario &usuario) {
  const std::string sql = "INSERT INTO Usuario (id, dni, username, password) VALUES "
                     "(NULL, ?, ?, ?);";

  sqlite3_stmt *stmt = db.preparar_consulta(sql);

  int result = db.execute_query(sql, &stmt);
  if (result != SQLITE_OK) {
    fprintf(stderr, "Error executing statement\n");
    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, usuario.getNombre().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, usuario.getContraseña().c_str(), -1,
                    SQLITE_STATIC);

  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE) {
    printf("Error executing DELETE\n");
    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_finalize(stmt);
}

void UserDAO::del(Usuario &usuario) {
  sqlite3_stmt *stmt;

  std::string sql = "DELETE FROM Usuario WHERE dni = ?;";

  int result = db.execute_query(sql, &stmt);

  if (result != SQLITE_OK) {
    printf("Error executing DELETE\n");
    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);

  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE) {
    printf("Error executing DELETE\n");
    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_finalize(stmt);
}

bool UserDAO::select(Usuario &usuario) {
  sqlite3_stmt *stmt;
  std::string sql = "SELECT dni, username, password FROM Usuario WHERE dni=?";
  int result = db.execute_query(sql, &stmt);
  if (result != SQLITE_OK) {
    printf("Error ejecutando SELECT\n");
    return false;
  }
  sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);
  if ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
    usuario.setDni(
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    usuario.setNombre(
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    usuario.setContraseña(
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
    return true;
  }

  if (result != SQLITE_ROW && result != SQLITE_DONE) {
    std::cout << "Error iterando sobre los resultados" << std::endl;
  }

  sqlite3_finalize(stmt);
  return false;
}

void UserDAO::update(Usuario &usuario) {
  sqlite3_stmt *stmt = nullptr;
  std::string sql =
      "UPDATE Usuario SET username = ?, password = ? WHERE dni = ?;";

  int result = db.execute_query(sql, &stmt);
  if (result != SQLITE_OK) {
    std::cout << "Error preparando consulta" << std::endl;
    return;
  }

  sqlite3_bind_text(stmt, 1, usuario.getNombre().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, usuario.getContraseña().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, usuario.getDni().c_str(), -1, SQLITE_STATIC);

  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE) {
    std::cout << "Error actualizando usuario" << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_finalize(stmt);
}

bool UserDAO::user_exists(const std::string &user,
                          const std::string &password) {
  sqlite3_stmt *stmt;
  const std::string sql = "SELECT dni, username, password FROM Usuario WHERE "
                          "username=? AND password=?";
  int result = db.execute_query(sql, &stmt);
  if (result != SQLITE_OK) {
    printf("Error ejecutando SELECT\n");
    return false;
  }
  sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  if ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return true;
  }

  if (result != SQLITE_ROW && result != SQLITE_DONE) {
    std::cout << "Error iterando sobre los resultados" << std::endl;
  }

  sqlite3_finalize(stmt);
  return false;
}

Usuario UserDAO::select_username(std::string &username)
{
  Usuario usuario;
  sqlite3_stmt *stmt;

  std::string sql = "SELECT dni, username, password FROM Usuario WHERE username = ?;";

  int result = db.execute_query(sql, &stmt);

  if (result != SQLITE_OK) {
    printf("Error executing SELECT\n");
    sqlite3_finalize(stmt);

  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  if ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
    usuario.setDni(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    usuario.setNombre(
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    return usuario;
  }

  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE) {
    printf("Error executing SELECT\n");
    sqlite3_finalize(stmt);
  }

  sqlite3_finalize(stmt);

  return usuario;
}
