
#include <QPushButton>
#include "mncstring.h"
extern "C"
QPushButton* QPushButton_new(const QIcon &icon,const char* text,QWidget* parent){
  return new (std::nothrow) QPushButton(icon,QString(text),parent);

}

extern "C"
QPushButton* QPushButton_new_v1(const char* text,QWidget* parent){
  return new (std::nothrow) QPushButton(QString(text),parent);

}

extern "C"
QPushButton* QPushButton_new_v2(QWidget* parent){
  return new (std::nothrow) QPushButton(parent);

}

extern "C"
QPushButton* QPushButton_new_v3(){
  return new (std::nothrow) QPushButton(nullptr);

}

extern "C"
void QPushButton_free(QPushButton** btn_hld){
  delete(*btn_hld);
  *btn_hld =nullptr;
}

extern "C"
void QPushButton_onclicked(  QAbstractButton* self
                           // Context of the callback. Note: C does not support closures 
                           // or stateful function pointer. All data needs to be passed 
                           // as arguments
                         , void* ctx
                           // Pointer to callback function pointer. 
                         , void (* callback) (void* ctx) )
{
    QObject::connect(self, &QPushButton::clicked, [=]{
        callback(ctx);
    });
}

extern "C"
char QpushBButton_is_checkable(QAbstractButton *self)
{
    return self->isCheckable();
}

extern "C"
char QpushBButton_is_checked(QAbstractButton *self)
{
    return self->isChecked();
}

extern "C"
char QpushBButton_is_down(QAbstractButton* self){
    return self->isDown();
}

extern "C"
char *QpushBButton_text(QAbstractButton *self)
{
    return  cstring_new_clone(self->text().toUtf8().data());
}

extern "C"
void QpushBButton_set_checkable(QAbstractButton *self, char state)
{
    self->setCheckable(state);
}

extern "C"
void QpushBButton_set_down(QAbstractButton *self, char state)
{
    self->setDown(state);
}

extern "C"
void QpushBButton_set_text(QAbstractButton *self, char *text)
{
    self->setText(QString(text));
}

extern "C"
void QpushBButton_set_click(QAbstractButton *self)
{
    self->click();
}

extern "C"
void QpushBButton_set_checked(QAbstractButton *self, char state)
{
    self->setChecked(state);
}
