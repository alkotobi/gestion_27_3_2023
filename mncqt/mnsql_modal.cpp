

#include "QSqlModal.h"

extern "C"
QSqlModal* mnsql_modal_new(QObject* parent) {
    return new (std::nothrow) QSqlModal(parent);
}

extern "C"
void mnsql_modal_fnc_col_count(QSqlModal* modal,int(*col_count)(void *)){
    modal->col_count = col_count;
}
extern "C"
void mnsql_modal_fnc_row_count(QSqlModal* modal,int(*row_count)(void*)){
    modal->row_count =row_count;
}
extern "C"
void mnsql_modal_fnc_cell_text(QSqlModal* modal,char*(*cell_text)(void*,int,int)){
    modal->cell_text =cell_text;
}
extern "C"
void mnsql_modal_fnc_cell_text_align(QSqlModal* modal,int(*cell_text_align)(void*,int,int)){
    modal->cell_text_align=cell_text_align;
}

extern "C"
void mnsql_modal_fnc_header_data(QSqlModal* modal,char*(*header_data)(void*,int,int,int)){
    modal->header_data = header_data;
}

extern "C"
void mnsql_modal_fnc_cell_background_color(QSqlModal* modal,int(*cell_background_color)(void*,int,int)){
    modal->cell_background_color =cell_background_color;
}

extern "C"
void mnsql_modal_fnc_cell_text_set_bold(QSqlModal* modal,char(*cell_text_set_bold)(void*,int,int)){
    modal->cell_text_set_bold=cell_text_set_bold;
}

extern "C"
void mnsql_modal_fnc_cell_text_set_font_family(QSqlModal* modal,char*(*cell_text_set_font_family)(void*,int,int)){
    modal->cell_text_set_font_family=cell_text_set_font_family;
}
extern "C"
void mnsql_modal_fnc_cell_text_set_font_italic(QSqlModal* modal,char(*cell_text_set_font_italic)(void*,int,int)){
    modal->cell_text_set_font_italic=cell_text_set_font_italic;
}
extern "C"
void mnsql_modal_fnc_cell_foreground_color(QSqlModal* modal,int(*cell_foreground_color)(void*,int,int)){
    modal->cell_foreground_color = cell_foreground_color;
}
extern "C"
void mnsql_modal_fnc_cell_set_checked(QSqlModal* modal,char(*cell_set_checked)(void*,int,int)){
    modal->cell_set_checked=cell_set_checked;
}
extern "C"
void mnsql_modal_fnc_set_data(QSqlModal* modal,char(*set_data)(void*,int,int,char*)){
    modal->set_data =set_data;
}

extern "C"
void mnsql_modal_fnc_remove_rows(QSqlModal* modal,char(*remove_row)(void*,int)){
    modal->remove_row=remove_row;
}

extern "C"
void mnsql_modal_fnc_insert_row(QSqlModal* modal,char(*insert_row)(void*,int)){
    modal->insert_row = insert_row;
}