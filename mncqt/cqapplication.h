#pragma once
#include "cqheader.h"
typedef void QApplication;

QApplication* QApplication_new(int argc, char** argv);
QApplication* QApplication_new_no_param();
int QApplication_exec(QApplication* self);
void QApplication_setActiveWindow(QApplication* self,QWidget *active);
QWidget *QApplication_activeWindow(QApplication *self);
