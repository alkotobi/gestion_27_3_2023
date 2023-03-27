#include <QWidget>

extern "C"
QWidget* QWidget_new_widget(QWidget *parent){
    return new QWidget(parent,Qt::Widget);
}

extern "C"
QWidget* QWidget_new_window(QWidget *parent){
    return new QWidget(parent,Qt::Window);
}

extern "C"
QWidget* QWidget_new_dialog(QWidget *parent){
    return new QWidget(parent,Qt::Dialog);
}

extern "C"
QWidget* QWidget_new_sheet(QWidget *parent){
    return new QWidget(parent,Qt::Sheet);
}

extern "C"
QWidget* QWidget_new_drawer(QWidget *parent){
    return new QWidget(parent,Qt::Drawer);
}

extern "C"
QWidget* QWidget_new_popup(QWidget *parent){
    return new QWidget(parent,Qt::Popup);
}

extern "C"
void QWidget_activate_window(QWidget *self)
{
    self->activateWindow();
}

extern "C"
void QWidget_adjust_size(QWidget *self)
{
    self->adjustSize();
}

extern "C"
QWidget *QWidget_focus_widget(QWidget *self)
{
    return self->focusWidget();
}

extern "C"
char QWidget_has_focus(QWidget *self)
{
    if(self->hasFocus()) return 1;else return 0;
}

extern "C"
int QWidget_height(QWidget *self)
{
    return self->height();
}

extern "C"
char QWidget_is_active_window(QWidget *self)
{
    if(self->isActiveWindow()) return 1;else return 0;
}

extern "C"
char QWidget_is_ancestor_of(QWidget *self,const QWidget *child)
{
    if(self->isAncestorOf(child)) return 1;else return 0;
}

extern "C"
char QWidget_is_enabled(QWidget *self)
{
   if(self->isEnabled()) return 1;else return 0;
}

extern "C"
char QWidget_is_full_screen(QWidget *self)
{
    if(self->isFullScreen()) return 1;else return 0;
}

extern "C"
char QWidget_is_hidden(QWidget *self)
{
    if(self->isHidden()) return 1;else return 0;
}

extern "C"
char QWidget_is_visible(QWidget *self)
{
    if(self->isVisible()) return 1;else return 0;
}


extern "C"
char QWidget_is_window(QWidget *self)
{
    if(self->isWindow()) return 1;else return 0;
}

extern "C"
QLayout *QWidget_layout(QWidget *self)
{
    return self->layout();
}

int QWidget_layoutDirection(QWidget *self)
{
    return self->layoutDirection();
}

extern "C"
QWidget *QWidget_next_in_focus_chain(QWidget *self)
{
    return self->nextInFocusChain();
}

extern "C"
QWidget *QWidget_parent_widget(QWidget *self)
{
    return self->parentWidget();
}

extern "C"
QWidget *QWidget_previous_in_focus_chain(QWidget *self)
{
    return self->previousInFocusChain();
}

extern "C"
void QWidget_scroll(QWidget *self, int dx, int dy)
{
    self->scroll(dx,dy);
}

extern "C"
void QWidget_set_parent(QWidget *self,QWidget *parent)
{
    self->setParent(parent);
}

extern "C"
int QWidget_width(QWidget *self)
{
    return self->width();
}

extern "C"
char QWidget_close(QWidget *self)
{
    return self->close();
}

extern "C"
void QWidget_hide(QWidget *self)
{
    self->hide();
}

extern "C"
void QWidget_lower(QWidget *self)
{
    self->lower();
}

extern "C"
void QWidget_raise(QWidget *self)
{
    self->raise();
}

extern "C"
void QWidget_repaint(QWidget *self)
{
    self->repaint();
}

extern "C"
void QWidget_set_disabled(QWidget *self, char disabled_state)
{
    self->setDisabled(disabled_state);
}

extern "C"
void QWidget_set_visible(QWidget *self, char hidden_state)
{
    self->setVisible(hidden_state);
}

extern "C"
void QWidget_set_style_sheet(QWidget *self, QString *style_sheet)
{
    self->setStyleSheet(*style_sheet);
}

extern "C"
void QWidget_set_window_modified(QWidget *self, char modified_state)
{
    self->setWindowModified(modified_state);
}

extern "C"
void QWidget_set_window_title(QWidget *self, QString *window_title)
{
    self->setWindowTitle(*window_title);
}

extern "C"
void QWidget_show(QWidget *self)
{
    self->show();
}

extern "C"
void QWidget_show_full_screen(QWidget *self)
{
    self->showFullScreen();
}

extern "C"
void QWidget_show_maximized(QWidget *self)
{
    self->showMaximized();
}

extern "C"
void QWidget_show_minimized(QWidget *self)
{
    self->showMinimized();
}

extern "C"
void QWidget_show_normal(QWidget *self)
{
    self->showNormal();
}

extern "C"
void QWidget_update(QWidget *self)
{
    self->update();
}

extern "C"
void QWidget_free(QWidget ** wid_hld)
{
    delete *wid_hld;
    *wid_hld=nullptr;
}

