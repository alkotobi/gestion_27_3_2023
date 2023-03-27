#pragma once
#include "cqheader.h"
typedef void QWidget;
typedef void QLayout;

QWidget* QWidget_new_window(QWidget *parent);
QWidget* QWidget_new_sheet(QWidget *parent);
QWidget* QWidget_new_drawer(QWidget *parent);
QWidget* QWidget_new_popup(QWidget *parent);
void QWidget_activate_window(QWidget *self);
void QWidget_adjust_size(QWidget *self);
QWidget *QWidget_focus_widget(QWidget *self);
char QWidget_has_focus(QWidget *self) ;
int QWidget_height(QWidget *self);
char QWidget_is_active_window(QWidget *self);
char QWidget_is_ancestor_of(QWidget *self,const QWidget *child);
char QWidget_is_enabled(QWidget *self);
char QWidget_is_full_screen(QWidget *self);
char QWidget_is_hidden(QWidget *self);
char QWidget_is_visible(QWidget *self);
char QWidget_is_window(QWidget *self);
QLayout *QWidget_layout(QWidget *self);
int  QWidget_layoutDirection(QWidget *self);
QWidget *QWidget_next_in_focus_chain(QWidget *self);
QWidget *QWidget_parent_widget(QWidget *self);
QWidget *QWidget_previous_in_focus_chain(QWidget *self);
void QWidget_scroll(QWidget *self,int dx, int dy);
void QWidget_set_parent(QWidget *self,QWidget *parent);
int QWidget_width(QWidget *self);
char QWidget_close(QWidget *self);
void QWidget_hide(QWidget *self);
void QWidget_lower(QWidget *self);
void QWidget_raise(QWidget *self);
void QWidget_repaint(QWidget *self);
void QWidget_set_disabled(QWidget *self,char disabled_state);
void QWidget_set_visible(QWidget *self,char hidden_state);
void QWidget_set_style_sheet(QWidget *self,QString* style_sheet);
void QWidget_set_window_modified(QWidget *self,char modified_state);
void QWidget_set_window_title(QWidget *self,QString* window_title);
void QWidget_show(QWidget *self);
void QWidget_show_full_screen(QWidget *self);
void QWidget_show_maximized(QWidget *self);
void QWidget_show_minimized(QWidget *self);
void QWidget_show_normal(QWidget *self);
void QWidget_update(QWidget *self);
void QWidget_free(QWidget ** wid_hld);

