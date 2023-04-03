//
// Created by merhab on 2023/4/3.
//

#include "tblmodal.h"

tblmodal *tblmodal_new() {
    tblmodal *lmodal = (tblmodal *) mnalloc(sizeof(tblmodal));
    mnassert(lmodal);
    lmodal->modal = 0;
    lmodal->datasset = 0;
    //ur code here

    return lmodal;
}

int tblmodal_column_count(void *lmodal) {
    mnassert(lmodal);
    tblmodal *modal = (tblmodal *) lmodal;
    return mnmetadata_list_generated_count(modal->datasset->meta_super->meta_list);
}

int tblmodal_row_count(void *lmodal) {
    mnassert(lmodal);
    tblmodal *modal = (tblmodal *) lmodal;
    return modal->datasset->recordset->count;
}

char * tblmodal_header_data(void* lmodal,int col, int row, int role){
    mnassert(lmodal);
    tblmodal *modal = (tblmodal *) lmodal;
    mnmetadata* meta = mnmetadata_list_item_at(modal->datasset->meta_super->meta_list,col);
    char* name=0;
    if (meta->caption) name = str_cpy(meta->caption);
    else name =str_cpy(meta->name);
    return name;
}

tblmodal *tblmodal_init(tblmodal *lmodal, mndataset *dataset, mnsql_modal *modal) {
    lmodal->modal = modal;
    lmodal->datasset = dataset;
    lmodal->col_count = tblmodal_column_count;
    mnsql_modal_fnc_col_count(lmodal->modal,tblmodal_column_count);
    lmodal->row_count = tblmodal_row_count;
    mnsql_modal_fnc_row_count(lmodal->modal,tblmodal_row_count);
    lmodal->header_data = tblmodal_header_data;
    mnsql_modal_fnc_header_data(lmodal->modal,tblmodal_header_data);
    return lmodal;
}

tblmodal *tblmodal_clean(tblmodal *lmodal) {
    return lmodal;
}

void tblmodal_free(tblmodal **lmodal_hld) {
    mnfree(*lmodal_hld);
    *lmodal_hld = 0;
}

void tblmodal_clean_free(tblmodal **lmodal_hld) {
    tblmodal_clean(*lmodal_hld);
    tblmodal_free(lmodal_hld);
}
