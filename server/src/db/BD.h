//
// Created by maddi.esparta on 29/05/2025.
//

#ifndef BD_H
#define BD_H
#include <string>

#include "Config.h"
#include "sqlite3.h"

class BD {
private:
    static BD* instance;
    sqlite3 *db;

    BD();
    ~BD();

public:
    static BD &get_instance();
    void abrir_conexion(const std::string&ruta = Config::get_config().get_db_path());
    void cerrar_conexion();


    int execute_query(std::string sql, sqlite3_stmt** stmt);
    sqlite3_stmt* preparar_consulta(const std::string&sql) const;
    int crear_tablas();
    sqlite3* get_db();
};



#endif //BD_H
