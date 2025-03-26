#include <stdio.h>
#include "bd.h"
#include "menus/menus.h"
#include "sqlite3.h"

int main()
{

    //crear base de datos
  //  sqlite3 *db;
   // int rc = sqlite3_open("bd.db", &db);

  //  if (rc != SQLITE_OK) {
   //     printf("No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
   //     return -1;
  //  }
    //if (crearTablas(db) != 0)
    ////      printf("Error creado tablas");
     //   sqlite3_close(db);
      ///  return 1;
    //}

  //  sqlite3_close(db);

    menuPrincipalAdmin();
    return 0;
}
