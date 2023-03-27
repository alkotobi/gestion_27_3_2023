#pragma once
#include "cqheader.h"

QLabel *QLabel_new(char* text,QWidget* parent,int window_flag);
void QLabel_free(QLabel** label_hld);
QString* QLabel_text(QLabel* self);
void QLabel_set_text(QLabel* self,char* text);
