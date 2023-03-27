#include <QTableView>

extern "C"
QTableView* QTableView_new(QWidget* parent){
    return new (std::nothrow) QTableView(parent);
}

extern "C"
void QTableView_set_modal(QTableView *view, QAbstractItemModel *modal)
{
    view->setModel(modal);
}


