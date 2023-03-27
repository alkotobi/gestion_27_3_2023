#include <QApplication>

extern "C"
QApplication* QApplication_new(int argc, char** argv)
{
  return new QApplication(argc, argv);
}

extern "C"
QApplication* QApplication_new_no_param()
{
  static int   argc = 1;
  static const char* argv [] = { "dummy_app" };
  return new QApplication(argc, (char**) argv);

}

extern "C"
int QApplication_exec(QApplication* self)
{
  return self->exec();
}

extern "C"
void QApplication_setActiveWindow(QApplication *self, QWidget *active)
{
  self->setActiveWindow(active);
}

extern "C"
QWidget *QApplication_activeWindow(QApplication *self)
{
  return self->activeWindow();
}

