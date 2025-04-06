#include "config.h"

#include <stdio.h>
#include <string.h>

static Config config = {};

void load_config()
{
    FILE* config_file = fopen(CONFIG_PATH, "r");
    if (config_file == NULL)
    {
        if (create_config_file())
        {
            config_file = fopen(CONFIG_PATH, "r");
        }
        else { return; }
    }


    int character = 0;
    int counter = 0;
    int position = 0;
    char temp[200];

    do
    {
        character = fgetc(config_file);
        if (character == '\n')
        {
            switch (position)
            {
                case 0:
                    strncpy(config.db_path, temp, sizeof(config.db_path) - 1);
                    break;
                case 1:
                    sscanf(temp, "%d", &config.color_output);
                    break;
                case 2:
                    sscanf(temp, "%d", &config.create_db_if_not_exists);
                    break;
                default:
                    break;
            }
            counter = 0;
            memset(temp,0,sizeof(temp));
            position++;
            continue;
        }
        temp[counter] = (char)character;
        counter++;

    }
    while (character != EOF);

    fclose(config_file);
}

int create_config_file()
{
    FILE* config_file = fopen(CONFIG_PATH, "w");
    if (config_file == NULL)
    {
        return 1;
    }
    fprintf(config_file, "../bd.db\n1\n1\n");
    fclose(config_file);
    return 0;
}

char* get_db_path()
{
    return config.db_path;
}

int create_db_if_not_exists()
{
    return config.create_db_if_not_exists;
}

int color_output()
{
    return config.color_output;
}