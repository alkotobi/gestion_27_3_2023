#pragma once

typedef void QString;

QString* QString_new();
QString* QString_new_from_cstring(const char* str);
void QString_free(QString** s_hld);
char QString_is_empty(QString* s);
char QString_is_right_to_left(QString*s);
double QString_to_double(QString*s);
int QString_to_int(QString*s);
QString* QString_add_cstring(QString*s,char* cstring);
QString* QString_add_QString(QString*s,QString* s_sub);
QString* QString_add_char(QString*s,char c);
char* QString_to_cstring_cpy(QString*s);
void QString_printf(QString* s); 
QString* QString_from_int(int n);
QString* QString_from_double(double f);
QString* QString_from_long(long int f);

