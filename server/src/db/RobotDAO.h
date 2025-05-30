//
// Created by naia.martin on 29/05/2025.
//

#ifndef ROBOTDAO_H
#define ROBOTDAO_H
#include <domain/Robot.h>

#include "sqlite3.h"


class RobotDAO {
    static sqlite3* db;
    RobotDAO();
private:
    bool insert(const Robot& &robot);
    bool update(const Robot& &robot);
    bool del(int id);
    Robot select(const Robot& &robot);
};



#endif //ROBOTDAO_H
