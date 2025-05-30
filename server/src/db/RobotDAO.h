//
// Created by naia.martin on 29/05/2025.
//

#ifndef ROBOTDAO_H
#define ROBOTDAO_H
#include <domain/Robot.h>

#include "bd.h"
#include "sqlite3.h"


class RobotDAO {
    static bd &db;
    RobotDAO();
private:
    void insert(const Robot& &robot);
    void update(const Robot& &robot);
    void del(const Robot &robot);
    Robot* select(const Robot& &robot);
};



#endif //ROBOTDAO_H
