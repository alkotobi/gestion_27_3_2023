#pragma once
#include <QAbstractTableModel>

class QSqlModal : public QAbstractTableModel
 {
     //Q_OBJECT

 public:
     QSqlModal(QObject* parent):QAbstractTableModel(parent){};
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;


     // QAbstractItemModel interface
    //  QModelIndex index(int row, int column, const QModelIndex &parent) const;
    //  QModelIndex parent(const QModelIndex &child) const;
     int columnCount(const QModelIndex &parent) const;
};