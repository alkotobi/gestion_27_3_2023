#pragma once
#include "cqheader.h"


QBoxLayout* QBoxLayout_new_left_to_right(QWidget* parent);
QBoxLayout* QBoxLayout_new_right_to_left(QWidget* parent);
QBoxLayout* QBoxLayout_new_top_to_bottom(QWidget* parent);
QBoxLayout* QBoxLayout_new_bottom_to_top(QWidget* parent);
void QBoxLayout_free(QBoxLayout** layout_hld);
void QBoxLayout_add_layout(QBoxLayout* self,QLayout* layout);
void QBoxLayout_add_spacing(QBoxLayout* self,int size);
void QBoxLayout_add_stretch(QBoxLayout* self,int stretch);
void QBoxLayout_add_widget
(QBoxLayout *self,QWidget *widget, int stretch,int alignement);
void QBoxLayout_add_widget_v1(QBoxLayout *self,QWidget *widget);
void QBoxLayout_insertLayout
(QBoxLayout *self,int index, QLayout *layout, int stretch);
void QBoxLayout_insert_spacing(QBoxLayout *self,int index, int size);
void QBoxLayout_insert_stretch(QBoxLayout *self,int index, int stretch);
void QBoxLayout_insert_widget
(QBoxLayout *self,int index, QWidget *widget, int stretch , int alignment );
void QBoxLayout_set_direction(QBoxLayout *self,int direction);
void QBoxLayout_set_pacing(QBoxLayout *self,int spacing);
void QBoxLayout_set_stretch(QBoxLayout *self,int index, int stretch);
int QBoxLayout_count(QBoxLayout *self);
QLayoutItem* QBoxLayout_item_at(QBoxLayout *self,int index);
QLayout* QLayoutItem_layout(QLayoutItem* self);
QWidget* QLayoutItem_widget(QLayoutItem* self);
QVBoxLayout* QVBoxLayout_new(QWidget *parent);
void QVBoxLayout_free(QVBoxLayout** vbox_hld);
QHBoxLayout* QHBoxLayout_new(QWidget *parent);
void QHBoxLayout_free(QHBoxLayout** vbox_hld);
QFormLayout* QFormLayout_new(QWidget* parent);
void QFormLayout_add_widget_as_row_with_lable(QFormLayout* self,QWidget* label,QWidget*  field);
void QFormLayout_add_layout_as_row_with_label(QFormLayout* self,QWidget* label,QLayout*  field);
void QFormLayout_add_widget_as_row_auto_lable(QFormLayout* self,char* label_cstring,QWidget*  field);
void QFormLayout_add_layout_as_row_auto_lable(QFormLayout* self,char* label_cstring,QLayout*  field);
void QFormLayout_add_widget_as_row(QFormLayout* self,QWidget*  field);
void QFormLayout_add_layout_as_row(QFormLayout* self,QLayout*  field);
QWidget* QFormLayout_lable_for_widget_field(QFormLayout* self,QWidget*  field);
QWidget* QFormLayout_lable_for_layout_field(QFormLayout* self,QLayout*  field);
void QFormLayout_remove_row_contains_widget(QFormLayout* self,QWidget*  field);
void QFormLayout_remove_row_contains_layout(QFormLayout* self,QLayout*  field);
void QFormLayout_remove_row_at(QFormLayout* self,int index);
int QFormLayout_row_count(QFormLayout* self);
void QFormLayout_set_form_alignment(QFormLayout* self,int alignement);
void QFormLayout_set_horizontal_spacing(QFormLayout* self,int spacing);
void QFormLayout_set_label_alignment(QFormLayout* self,int alignement);
void QFormLayout_set_vertical_spacing(QFormLayout* self,int spacing);
int  QFormLayout_vertical_spacing(QFormLayout* self);
int  QFormLayout_horizontal_spacing(QFormLayout* self);
int  QFormLayout_count(QFormLayout* self);
void QFormLayout_free(QFormLayout** layout_hld);
QGridLayout* QGridLayout_new(QWidget* parent);
void QGridLayout_add_layout(QGridLayout* self ,QLayout* layout,int row,int col,int alignment);
void QGridLayout_add_widget(QGridLayout* self ,QWidget* widget,int row,int col,int alignment);
int  QGridLayout_col_count(QGridLayout* self);
int QGridLayout_row_count(QGridLayout* self);
void QGridLayout_set_alignment(QGridLayout* self,int alignement);
void QGridLayout_set_horizontal_spacing(QGridLayout* self,int spacing);
void QGridLayout_set_vertical_spacing(QGridLayout* self,int spacing);
int  QGridLayout_vertical_spacing(QGridLayout* self);
int  QGridLayout_horizontal_spacing(QGridLayout* self);
int  QGridLayout_count(QGridLayout* self);
void QGridLayout_free(QGridLayout** layout_hld);


