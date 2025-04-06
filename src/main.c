#include <stdio.h>

#include "config.h"
#include "db/bd_new.h"
#include "menu.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main()
{
    load_config();
    if (color_output())
    {
        printf(ANSI_COLOR_GREEN);
    }
    init_db();
    initializeMenus(get_db());
    close_db();
    return 0;
}
