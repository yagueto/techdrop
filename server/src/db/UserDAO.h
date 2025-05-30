#ifndef USERDAO_H
#define USERDAO_H
#include <sqlite3.h>
#include <domain/Usuario.h>
#include "bd.h"

class UserDAO {
    static bd &db;
    UserDAO();
public:
    static void insert(Usuario &usuario);
    static void del(Usuario &usuario);
    static Usuario* select(Usuario &usuario);
};



#endif //USERDAO_H
