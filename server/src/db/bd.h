//
// Created by maddi.esparta on 29/05/2025.
//

#ifndef BD_H
#define BD_H
#include <string>
#include "sqlite3.h"

class bd {
private:
    static bd* instance;
    sqlite3 *db;

    bd();
    ~bd();

public:
    static bd &get_instance();
    void abrir_conexion(const std::string&ruta = "../bd.db");
    void cerrar_conexion();


    int execute_query(const std::string&sql);
    sqlite3_stmt* preparar_consulta(const std::string&sql);

};



#endif //BD_H
