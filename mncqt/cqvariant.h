#pragma once
#include "cqstring.h"

typedef void QVariant;

QVariant* QVariant_new();
QVariant* QVariant_new_from_cstring(char* cstring);
QVariant* QVariant_new_from_int(int n);
QVariant* QVariant_new_from_double(double f);
QVariant* QVariant_new_from_QString(QString* s);//TODO: QVariant_new_from_QString leak possible of memory here
char QVariant_can_convert(QVariant* self,int type_id);
int QVariant_to_int(QVariant* self);
double QVariant_to_double(QVariant* self);
QString* QVariant_to_QString(QVariant* self);
void QVariant_free(QVariant** var_hld);
