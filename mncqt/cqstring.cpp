#include <QString>
#include "mncstring.h"

extern "C" QString* QString_new(){
    QString* s= new (std::nothrow) QString();
    return s;
}
extern "C" QString* QString_new_from_cstring(const char* str){
    QString* s= new (std::nothrow) QString(str);   
    return s;
}
extern "C" void QString_free(QString** s_hld){
    delete *s_hld;
    *s_hld=nullptr;
}
extern "C" char QString_is_empty(QString* s){
    if(s->isEmpty()){
        return 1;
    }else {
        return 0;
    }
}
extern "C" char QString_is_right_to_left(QString*s){

    if (s->isRightToLeft()) {
        return 1;
    }else return 0;
}
extern "C" double QString_to_double(QString*s){
    return s->toDouble();
}
extern "C" int QString_to_int(QString*s){
    return s->toInt();
}

extern "C" QString* QString_add_cstring(QString*s,char* cstring){
    *s=*s+cstring;
    return s;
}

extern "C" QString* QString_add_QString(QString*s,QString* s_sub){
    *s=*s+*s_sub;
    return s;
}

extern "C" QString* QString_add_char(QString*s,char c){
    s->append(c);
    return s;
}

extern "C"
char* QString_to_cstring_cpy(QString*s){
    return cstring_new_clone(s->toUtf8().data());
}

extern "C"
void QString_printf(QString* s){
    printf("%s",s->toUtf8().data()) ;
}

extern "C"
QString* QString_from_int(int n)
{
    QString* s = new (std::nothrow) QString();
    *s = QString::number(n);
    return s;
}

extern "C"
QString* QString_from_double(double f)
{
    QString* s = new (std::nothrow) QString();
    *s = QString::number(f);
    return s;
}

extern "C"
QString* QString_from_long(long int f)
{
    QString* s = new (std::nothrow) QString();
    *s = QString::number(f);
    return s;
}

