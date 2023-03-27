
#include<QDebug>

extern "C"
void cqInfo(const char* msg) {
    qInfo()<< msg;
}

extern "C"
void cqDebug( const char* msg){
    qDebug() << msg;
}
extern "C"
void cqWarning(const char* msg ){
    qWarning() << msg;
}

extern "C"
void cqCritical( const char* msg ) {
    qCritical()<< msg;
}
extern "C"
void cqFatal( const char* msg) {
    qFatal("%s", "%s",msg);
}
