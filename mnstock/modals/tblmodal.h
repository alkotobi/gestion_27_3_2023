//
// Created by merhab on 2023/4/3.
//

#pragma once
#include "mndataset.h"
#include "mnsql_modal.h"

typedef struct {
    mndataset* datasset;
    mnsql_modal* modal;

    int (*col_count)(void*)  ;//d
    int (*row_count)(void*)  ;//d
    ///
    /// \return the column title
    /// \brief get 3 int section/oriantation :Horizontal = 1,Vertical = 2/role
    char *(*header_data)(void*,int, int, int)  ;//d
    ///
    /// \return the color of the cell background
    /// \brief get 2 int: col , row and return the color cod

    int (*cell_background_color)(void*,int, int)  ;//d
    ///
    ///
    /// \brief get 2 int: col , row and return the alignement of the text
    int (*cell_text_align)(void*,int, int)  ;//d
    char *(*cell_text)(void*,int, int)  ;//d
    ///
    /// \brief get int col,int col
    char (*cell_text_set_bold)(void*,int, int) ;//d
    char* (*cell_text_set_font_family)(void*,int, int) ;//d
    char (*cell_text_set_font_italic)(void*,int, int) ;//d
    int (*cell_foreground_color)(void*,int, int) ;//d
    char (*cell_set_checked)(void*,int, int) ;//d
    char (*set_data)(void*,int,int,char* ) ;//d
    char (*remove_row)(void*,int) ;//d
    char (*insert_row)(void*,int);

}tblmodal;

tblmodal* tblmodal_new();
tblmodal* tblmodal_init(tblmodal* lmodal,mndataset* dataset,mnsql_modal* modal);
tblmodal* tblmodal_clean(tblmodal* lmodal);
void tblmodal_free(tblmodal** lmodal_hld);
void tblmodal_clean_free(tblmodal** lmodal_hld);
int tblmodal_column_count(void* lmodal);
int tblmodal_row_count(void *lmodal);
char * tblmodal_header_data(void* lmodal,int col, int row, int role);
