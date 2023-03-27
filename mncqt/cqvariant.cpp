
#include <QVariant>
extern "C"
QVariant* QVariant_new(){
    return new (std::nothrow) QVariant();
}

extern "C"
QVariant* QVariant_new_from_cstring(char* cstring){
    return new (std::nothrow) QVariant(QString(cstring));
}

extern "C"
QVariant* QVariant_new_from_int(int n){
    return new (std::nothrow) QVariant(n);
}

extern "C"
QVariant* QVariant_new_from_double(double f){
    return new (std::nothrow) QVariant(f);
}

extern "C"
QVariant* QVariant_new_from_QString(QString* s){
    return new (std::nothrow) QVariant(*s);
}

extern "C"
char QVariant_can_convert(QVariant* self,int type_id){
    return self->canConvert(type_id);
}

extern "C"
int QVariant_to_int(QVariant* self){
    return self->toInt();
}

extern "C"
double QVariant_to_double(QVariant* self){
    return self->toDouble();
}

extern "C"
QString* QVariant_to_new_QString(QVariant* self){
    QString* s =new(std::nothrow) QString();
    *s= self->toString();
    return s;
}

extern "C"
void QVariant_free(QVariant** var_hld){
    delete *var_hld;
    *var_hld=nullptr;
}

