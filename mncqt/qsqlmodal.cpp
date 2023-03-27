#include "qsqlmodal.h"

int QSqlModal::rowCount(const QModelIndex &parent) const {
    return 5;
}

QVariant QSqlModal::data(const QModelIndex &index, int role) const {
    return QVariant(5);
}

QVariant QSqlModal::headerData(int section, Qt::Orientation orientation,
                                int role) const {
    return QVariant(12);
}

int QSqlModal::columnCount(const QModelIndex &parent) const {
    return 3;
}



