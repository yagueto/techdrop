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
    static void update(Usuario &usuario);
    static bool select(Usuario &usuario);
    static bool user_exists(const std::string &user,
                            const std::string &password);
};



#endif //USERDAO_H
