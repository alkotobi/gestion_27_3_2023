#include <QLabel>
#include "mncstring.h"
extern "C"
QLabel *QLabel_new(const char* text,QWidget* parent,int window_flag){
  return new (std::nothrow) QLabel(text,parent,(Qt::WindowFlags)window_flag);
}


extern "C"
char *QLabel_text(QLabel *self)
{
  //QString* s = new (std::nothrow) QString;
  return cstring_new_clone(self->text().toUtf8().data());
  //return s;
}

extern "C"
void QLabel_set_text(QLabel *self, char *text)
{
  self->setText(QString(text));
}

void QLabel_free(QLabel** label_hld){
  delete (*label_hld);
  *label_hld =nullptr;
}
