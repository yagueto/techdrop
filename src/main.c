#include "db/bd_new.h"
#include "menu.h"

int main()
{
    init_db();
    initializeMenus(get_db());
    close_db();
    return 0;
}
