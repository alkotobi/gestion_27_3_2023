

#include "qsqlmodal.h"

extern "C"
QSqlModal* CQSqlModal_new(QObject* parent) {
    return new (std::nothrow) QSqlModal(parent);
}

