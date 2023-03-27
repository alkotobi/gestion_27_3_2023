#include "cqStandardPaths_t.h"

char cqStandardPaths_test()
{
    char *path=QStandardPaths_writableLocation(QStandardPaths_AppDataLocation);
    print_green(path);
    print_green("\n");
    return 1;
}