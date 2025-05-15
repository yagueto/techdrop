#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_PATH "../config.properties"

typedef struct
{
    char db_path[200];
    int color_output;
    int create_db_if_not_exists;
} Config;

void load_config();
int create_config_file();
char* get_db_path();
int create_db_if_not_exists();
int color_output();

#endif //CONFIG_H
