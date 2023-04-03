#include <QtGui/qfont.h>
#include <QBrush>
#include "QSqlModal.h"
#include <QString>
#include "qt_const.h"


int QSqlModal::rowCount(const QModelIndex &parent) const {
    if (!row_count) return 1;
    return row_count(dataset);
}

QVariant QSqlModal::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    qDebug() << QString("row %1, col%2, role %3")
            .arg(row).arg(col).arg(role);
    char *str;
    QString qstr;
    switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (!cell_text) str = "nullptr";
            else str = cell_text(dataset,col, row);
            qstr = QString(str);
            //free(str);
            return qstr;
        case Qt::FontRole: {
            QFont boldFont;
            if (cell_text_set_bold) boldFont.setBold((bool) cell_text_set_bold(dataset,col, row));
            if (cell_text_set_font_family) {
                str = cell_text_set_font_family(dataset,col, row);
                boldFont.setFamily(QString(str));
                free(str);
            }
            if (cell_text_set_font_italic)
                boldFont.setItalic((bool) cell_text_set_font_italic(dataset,col, row));
            return boldFont;
        }
            break;
        case Qt::BackgroundRole:
            if (cell_background_color)
                return QBrush((Qt::GlobalColor) cell_background_color(dataset,col, row));
            break;
        case Qt::ForegroundRole:
            if (cell_foreground_color)
                return QColor((Qt::GlobalColor) cell_foreground_color(dataset,col, row));
            break;
        case Qt::TextAlignmentRole:
            if (cell_text_align)
                return (Qt::AlignmentFlag) cell_text_align(dataset,col, row);
            break;
        case Qt::CheckStateRole:
            if (cell_set_checked)
                return (Qt::CheckState) cell_set_checked(dataset,col, row);
            break;
    }
    return QVariant();


}

QVariant QSqlModal::headerData(int section, Qt::Orientation orientation,
                               int role) const {
    if (!header_data) return QVariant(QString(""));
    char *str = header_data(dataset,section, orientation, role);
    QVariant var = QVariant(QString(str));
    free(str);
    return var;
}

int QSqlModal::columnCount(const QModelIndex &parent) const {
    if (!col_count) return 1;
    return col_count(dataset);
}

bool QSqlModal::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        const int col = index.column();
        char ret=0;
        if (set_data){
            char* str=value.toString().toUtf8().data();
             ret = set_data(dataset,col,row,str);
        }
        //auto contact = contacts.value(row);

        switch (index.column()) {
            case 0:
                //contact.name = value.toString();
                break;
            case 1:
                //contact.address = value.toString();
                break;
            default:
                return false;
        }
        //contacts.replace(row, contact);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return (bool )ret;
    }

    return false;
}

Qt::ItemFlags QSqlModal::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool QSqlModal::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    char ret=1;
    if (remove_row) {
        for (int row = 0; row < rows; ++row)
            ret*=remove_row(dataset,position);
        //contacts.removeAt(position);
    }
        endRemoveRows();
    return ret;
}

bool QSqlModal::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    char ret=1;
    if (insert_row) {
        for (int row = 0; row < rows; ++row)
            ret*=insert_row(dataset,position);
        //contacts.insert(position, { QString(), QString() });
    }
        endInsertRows();
    return ret;
}