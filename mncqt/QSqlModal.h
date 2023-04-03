#pragma once

#include <QAbstractTableModel>


class QSqlModal : public QAbstractTableModel {
    //Q_OBJECT

public:
    QSqlModal(QObject *parent) : QAbstractTableModel(parent) {};

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;


    // QAbstractItemModel interface
    //  QModelIndex index(int row, int column, const QModelIndex &parent) const;
    //  QModelIndex parent(const QModelIndex &child) const;
    int columnCount(const QModelIndex &parent) const;

    int (*col_count)(void*dataset) = 0;//d
    int (*row_count)(void*dataset) = 0;//d
    ///
    /// \return the column title
    /// \brief get 3 int section/oriantation :Horizontal = 1,Vertical = 2/role=0
    char *(*header_data)(void*dataset,int col, int row, int role) = 0;//d
    ///
    /// \return the color of the cell background
    /// \brief get 2 int: col , row and return the color cod

    int (*cell_background_color)(void*dataset,int col, int row) = 0;//d
    ///
    ///
    /// \brief get 2 int: col , row and return the alignement of the text
    int (*cell_text_align)(void*dataset,int col, int row) = 0;//d
    char *(*cell_text)(void*dataset,int col, int row) = 0;//d
    ///
    /// \brief get int col,int col
    char (*cell_text_set_bold)(void*dataset,int col, int row)=0;//d
    char* (*cell_text_set_font_family)(void*dataset,int col, int row)=0;//d
    char (*cell_text_set_font_italic)(void*dataset,int col, int row)=0;//d
    int (*cell_foreground_color)(void*dataset,int col, int row) = 0;//d
    char (*cell_set_checked)(void*dataset,int col, int row)=0;//d
    char (*set_data)(void*dataset,int col,int row,char* data )=0;//d
    char (*remove_row)(void*dataset,int position)=0;//d
    char (*insert_row)(void* dataset,int position)=0;
    void* dataset;
};