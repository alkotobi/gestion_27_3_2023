#include <QLineEdit>

extern "C"
QLineEdit* QLineEdit_new(const char* text,QWidget* parent) {
    return new (std::nothrow) QLineEdit(QString(text),parent);
}
