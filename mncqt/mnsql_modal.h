#pragma once
#include "cqheader.h"
typedef QSqlModal mnsql_modal;
mnsql_modal* mnsql_modal_new(QObject* parent);
void mnsql_modal_fnc_col_count(mnsql_modal* modal,int(*col_count)(void*));
void mnsql_modal_fnc_row_count(mnsql_modal* modal,int(*row_count)(void*));
void mnsql_modal_fnc_cell_text(mnsql_modal* modal,char*(*cell_text)(void*,int,int));
void mnsql_modal_fnc_cell_text_align(mnsql_modal* modal,int(*cell_text_align)(void*,int,int));
///
/// \param header_data  a function that get 3 int section/oriantation :Horizontal = 1,Vertical = 2/role=0
void mnsql_modal_fnc_header_data(mnsql_modal* modal,char*(*header_data)(void*,int,int,int));
void mnsql_modal_fnc_cell_background_color(mnsql_modal* modal,int(*cell_background_color)(void*,int,int));
void mnsql_modal_fnc_cell_text_set_bold(mnsql_modal* modal,char(*cell_text_set_bold)(void*,int,int));
void mnsql_modal_fnc_cell_text_set_font_family(mnsql_modal* modal,char*(*cell_text_set_font_family)(void*,int,int));
void mnsql_modal_fnc_cell_text_set_font_italic(mnsql_modal* modal,char(*cell_text_set_font_italic)(void*,int,int));
void mnsql_modal_fnc_cell_foreground_color(mnsql_modal* modal,int(*cell_foreground_color)(void*,int,int));
void mnsql_modal_fnc_cell_set_checked(mnsql_modal* modal,char(*cell_set_checked)(void*,int,int));
void mnsql_modal_fnc_set_data(mnsql_modal* modal,char(*set_data)(void*,int,int,char*));
void mnsql_modal_fnc_remove_rows(mnsql_modal* modal,char(*remove_row)(void*,int));
void mnsql_modal_fnc_insert_row(mnsql_modal* modal,char(*insert_row)(void*,int));