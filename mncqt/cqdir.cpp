
#include <QDir>
#include <QString>
#include "mncstring.h"

extern "C" char *QDir_separator() {
    QChar c= QDir::separator();
    char *str=cstring_new_v0(1);
    str[0]=c.toLatin1();
    return str;
}

extern "C" char *QDir_cleanPath(char *path){
    QString str= QDir::cleanPath(QString(path));
    return cstring_new_clone(str.toUtf8().data());
}

extern "C" char QDir_mkdir(char *path) {

    bool res=QDir().mkdir(QString(path));
    if (res){
        return 1;
    }
    return 0;
}

extern "C" char QDir_exists(char *path){
    if (QDir(QString(path)).exists())
    {
        return 1;
    }
    return 0;
} 


