//
// Created by asier.amigorena on 29/05/2025.
//

#include "Config.h"
#include <string>
#include <iostream>
using namespace std;

const string Config::path = "../config.properties";

Config::Config() {
    load_config();
}

Config &Config::get_config() {
    static Config config;
    return config;
}

void Config::load_config() {
    config_file.open(path, ios::in);
    if (!config_file.is_open()) {
        if (create_config_file() != 0) {
            cout << "Error al abrir el fichero de configuración" << endl;
            return;
        }
    }

    string line;
    int pos = 0;
    while (getline(config_file, line)) {
        switch (pos) {
            case 0:
                db_path = line;
                break;
            case 1:
                log_path = line;
                break;
            case 2:
                create_db_if_not_exists = stoi(line);
                break;
            default:
                break;
        }
        pos++;
    }
    config_file.close();
}

int Config::create_config_file() {
    config_file.open(path, ios::out);
    if (!config_file.is_open()) {
        return 1;
    }
    config_file << "../bd.db\n../server.log\n1\n";
    config_file.close();
    return 0;
}


string Config::get_db_path() {
    return db_path;
}

string Config::get_log_path() {
    return log_path;
}

int Config::get_create_db_if_not_exists() const {
    return create_db_if_not_exists;
}
