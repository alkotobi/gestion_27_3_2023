#pragma once
#include "cqheader.h"

QPushButton* QPushButton_new(QIcon* icon,const char* text,QWidget* parent);
QPushButton* QPushButton_new_v1(const char* text,QWidget* parent);
QPushButton* QPushButton_new_v2(QWidget* parent);
QPushButton* QPushButton_new_v3();
void QPushButton_onclicked(QAbstractButton* self , void* ctx, void (* callback) (void* ctx) );
char QpushBButton_is_checkable(QAbstractButton* self);
char QpushBButton_is_checked(QAbstractButton* self);
char QpushBButton_is_down(QAbstractButton* self);
char* QpushBButton_text(QAbstractButton* self);
void QpushBButton_set_checkable(QAbstractButton* self,char state);
void QpushBButton_set_down(QAbstractButton* self,char state);
void QpushBButton_set_text(QAbstractButton* self,char* text);
void QpushBButton_set_click(QAbstractButton* self);
void QpushBButton_set_checked(QAbstractButton* self,char state);
