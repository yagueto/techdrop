//
// Created by asier.amigorena on 29/05/2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
using namespace std;

class Config {
    fstream config_file;
    static const string path;
    string db_path;
    int color_output = 1;
    int create_db_if_not_exists = 1;
    Config();
public:
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;
    Config static &get_config();
    void load_config();
    int create_config_file();
    string get_db_path();
    int get_color_output() const;
    int get_create_db_if_not_exists() const;
};



#endif //CONFIG_H
