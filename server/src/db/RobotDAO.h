//
// Created by naia.martin on 29/05/2025.
//

#ifndef ROBOTDAO_H
#define ROBOTDAO_H
#include <domain/Robot.h>

#include "bd.h"



class RobotDAO {
    static bd &db;
    RobotDAO();
private:
    static void insert(const Robot& &robot);

    static void update(const Robot& &robot);

    static void del(const Robot &robot);

    static Robot* select(const Robot& &robot);
};



#endif //ROBOTDAO_H
