#ifndef BD_NEW_H
#define BD_NEW_H
#include <sqlite3.h>

int init_db(void);
void close_db(void);
sqlite3* get_db(void);

int crear_tablas(void);
int execute_query(const char* sql, sqlite3_stmt** stmt);
int generar_datos_prueba();
#endif //BD_NEW_H
