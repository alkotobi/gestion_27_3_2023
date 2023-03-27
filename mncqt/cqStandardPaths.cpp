#include <QStandardPaths>
#include "mncstring.h"

extern "C" char *QStandardPaths_writableLocation(int std_path) {
    QString str= QStandardPaths::writableLocation((QStandardPaths::StandardLocation) std_path);
    return cstring_new_clone(str.toUtf8().data());
}
