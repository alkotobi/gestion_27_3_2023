
#include <QLayout>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>




extern "C"
QBoxLayout* QBoxLayout_new_left_to_right(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::LeftToRight,parent);
}

extern "C"
QBoxLayout* QBoxLayout_new_right_to_left(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::RightToLeft,parent);
}

extern "C"
QBoxLayout* QBoxLayout_new_top_to_bottom(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::TopToBottom,parent);
}

extern "C"
QBoxLayout* QBoxLayout_new_bottom_to_top(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::BottomToTop,parent);
}

extern "C"
void QBoxLayout_free(QBoxLayout** layout_hld){
    delete *layout_hld;
    *layout_hld=nullptr;
}

extern "C"
void QBoxLayout_add_layout(QBoxLayout *self, QLayout *layout)
{
    self->addLayout(layout);
}

extern "C"
void QBoxLayout_add_spacing(QBoxLayout *self, int size)
{
    self->addSpacing(size);
}

extern "C"
void QBoxLayout_add_stretch(QBoxLayout *self, int stretch)
{
    self->addStretch(stretch);
}

extern "C"
void QBoxLayout_add_widget(QBoxLayout *self,QWidget *widget,
 int stretch,int alignement)
{
    self->addWidget(widget,stretch,(Qt::Alignment)alignement);
}

extern "C"
void QBoxLayout_add_widget_v1(QBoxLayout *self,QWidget *widget) {
    self->addWidget(widget,0,(Qt::Alignment)0);
}


extern "C"
void QBoxLayout_insertLayout(QBoxLayout *self, int index, QLayout *layout, int stretch)
{
    self->insertLayout(index,layout,stretch);
}

extern "C"
void QBoxLayout_insert_spacing(QBoxLayout *self, int index, int size)
{
    self->insertSpacing(index,size);
}

extern "C"
void QBoxLayout_insert_stretch(QBoxLayout *self, int index, int stretch)
{
    self->insertStretch(index,stretch);
}

extern "C"
void QBoxLayout_insert_widget(QBoxLayout *self,int index, QWidget *widget, int stretch, int alignment)
{
    self->insertWidget(index,widget,stretch,(Qt::Alignment)alignment);
}


extern "C"
void QBoxLayout_set_direction(QBoxLayout *self, int direction)
{
    self->setDirection((QBoxLayout::Direction)direction);
}

extern "C"
void QBoxLayout_set_pacing(QBoxLayout *self, int spacing)
{
    self->setSpacing(spacing);
}

extern "C"
void QBoxLayout_set_stretch(QBoxLayout *self, int index, int stretch)
{
    self->setStretch(index,stretch);
}

extern "C"
int QBoxLayout_count(QBoxLayout *self)
{
    return self->count();
}

extern "C"
QLayoutItem *QBoxLayout_item_at(QBoxLayout *self, int index)
{
    return self->itemAt(index);
}

extern "C"
QLayout *QLayoutItem_layout(QLayoutItem *self)
{
    return self->layout();
}

extern "C"
QWidget *QLayoutItem_widget(QLayoutItem *self)
{
    return self->widget();
}

extern "C"
QVBoxLayout *QVBoxLayout_new(QWidget *parent)
{
    return new QVBoxLayout(parent);
}

extern "C"
void QVBoxLayout_free(QVBoxLayout **vbox_hld)
{
    delete *vbox_hld;
    *vbox_hld=nullptr;
}

extern "C"
QHBoxLayout *QHBoxLayout_new(QWidget *parent)
{
    return new QHBoxLayout(parent);
}

extern "C"
void QHBoxLayout_free(QHBoxLayout **vbox_hld)
{
    delete *vbox_hld;
    *vbox_hld=nullptr;
}

extern "C"
QFormLayout *QFormLayout_new(QWidget *parent)
{
    return new (std::nothrow) QFormLayout(parent);
}

extern "C"
void QFormLayout_add_widget_as_row_with_lable(QFormLayout *self,QWidget* label, QWidget *field)
{
    self->addRow(label,field);
}

extern "C"
void QFormLayout_add_layout_as_row_with_label(QFormLayout *self,QWidget* label, QLayout *field)
{
    self->addRow(label,field);
}

extern "C"
void QFormLayout_add_widget_as_row_auto_lable(QFormLayout *self, char *label_cstring, QWidget *field)
{
    self->addRow(QString(label_cstring),field);
}

extern "C"
void QFormLayout_add_layout_as_row_auto_lable(QFormLayout *self, char *label_cstring, QLayout *field)
{
    self->addRow(QString(label_cstring),field);
}

extern "C"
void QFormLayout_add_widget_as_row(QFormLayout *self, QWidget *field)
{
    self->addRow(field);
}

extern "C"
void QFormLayout_add_layout_as_row(QFormLayout *self, QLayout *field)
{
    self->addRow(field);
}

extern "C"
QWidget *QFormLayout_lable_for_widget_field(QFormLayout *self, QWidget *field)
{
    return self->labelForField(field);
}

extern "C"
QWidget *QFormLayout_lable_for_layout_field(QFormLayout *self, QLayout *field)
{
    return self->labelForField(field);
}

extern "C"
void QFormLayout_remove_row_contains_widget(QFormLayout *self, QWidget *field)
{
    self->removeRow(field);
}

extern "C"
void QFormLayout_remove_row_contains_layout(QFormLayout *self, QLayout *field)
{
    self->removeRow(field);
}

extern "C"
void QFormLayout_remove_row_at(QFormLayout *self, int index)
{
    self->removeRow(index);
}

extern "C"
int QFormLayout_row_count(QFormLayout *self)
{
    return self->rowCount();
}

extern "C"
void QFormLayout_set_form_alignment(QFormLayout *self, int alignement)
{
    self->setFormAlignment((Qt::Alignment)alignement);
}

extern "C"
void QFormLayout_set_horizontal_spacing(QFormLayout *self, int spacing)
{
    self->setHorizontalSpacing(spacing);
}

extern "C"
void QFormLayout_set_label_alignment(QFormLayout *self, int alignement)
{
    self->setLabelAlignment((Qt::Alignment)alignement);
}

extern "C"
void QFormLayout_set_vertical_spacing(QFormLayout *self, int spacing)
{
    self->setVerticalSpacing(spacing);
}

extern "C"
int QFormLayout_vertical_spacing(QFormLayout *self)
{
    return self->verticalSpacing();
}

extern "C"
int QFormLayout_horizontal_spacing(QFormLayout *self)
{
    return self->horizontalSpacing();
}

extern "C"
int QFormLayout_count(QFormLayout *self)
{
    return self->count();
}

extern "C"
void QFormLayout_free(QFormLayout **layout_hld)
{
    delete *layout_hld;
    *layout_hld=nullptr;
}

extern "C"
QGridLayout *QGridLayout_new(QWidget *parent)
{
    return new (std::nothrow) QGridLayout(parent);
}

extern "C"
void QGridLayout_add_layout(QGridLayout *self, QLayout *layout, int row, int col, int alignment)
{
    self->addLayout(layout,row,col,(Qt::Alignment)alignment);
}

extern "C"
void QGridLayout_add_widget(QGridLayout *self, QWidget *widget, int row, int col, int alignment)
{
    self->addWidget(widget,row,col,(Qt::Alignment)alignment);
}

extern "C"
int QGridLayout_col_count(QGridLayout *self)
{
    return self->columnCount();
}

extern "C"
int QGridLayout_row_count(QGridLayout *self)
{
    return self->rowCount();
}

extern "C"
void QGridLayout_set_alignment(QGridLayout *self, int alignement)
{
    self->setAlignment((Qt::Alignment)alignement);
}

extern "C"
void QGridLayout_set_horizontal_spacing(QGridLayout *self, int spacing)
{
    self->setHorizontalSpacing(spacing);
}

extern "C"
void QGridLayout_set_vertical_spacing(QGridLayout *self, int spacing)
{
    self->setVerticalSpacing(spacing);
}

extern "C"
int QGridLayout_vertical_spacing(QGridLayout *self)
{
    return self->verticalSpacing();
}

extern "C"
int QGridLayout_horizontal_spacing(QGridLayout *self)
{
    return self->horizontalSpacing();
}

extern "C"
int QGridLayout_count(QGridLayout *self)
{
    return self->count();
}

extern "C"
void QGridLayout_free(QGridLayout **layout_hld)
{
    delete *layout_hld;
    *layout_hld=nullptr;
}

