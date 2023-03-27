#pragma once
#include "cqheader.h"

QTableView* QTableView_new(QWidget* parent);
void QTableView_set_modal(QTableView* view,QAbstractItemModel* modal);
