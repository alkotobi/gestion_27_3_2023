//
// Created by merhab on 2023/3/26.
//

#include "mndataset.h"

mndataset *mndataset_new() {
    mndataset* d = (mndataset*) mnalloc(sizeof(mndataset));
    mnassert(d);
    d->recordset=0;
    d->tblsuper=0;
    return d;
}

mndataset *mndataset_init(mndataset *dataset, tbl_super *tblsuper, mndatabase *db, mnsql *msql) {
    if (!dataset) dataset = mndataset_new();
    dataset->tblsuper=tblsuper;
    dataset->db=db;
    dataset->sql=msql;
    return dataset;
}

mndataset *mndataset_clean_recordset(mndataset *dataset) {
    mnrecordset_clean_free(&dataset->recordset);
    return dataset;
}

void mndataset_free(mndataset **dataset_hld) {
    mnfree(*dataset_hld);
    *dataset_hld =0;
}

char mndataset_create_table(mndataset* dataset) {
    char* sql= mnsql_create_table_v0(dataset->tblsuper->table_name,dataset->tblsuper->meta_list);
    char ret=mndatabase_exec(dataset->db,sql);
    cstring_free_v0(sql);
    return ret;
}

mnsql_params *mnsql_params_new() {
    mnsql_params* sp = (mnsql_params*) mnalloc(sizeof(mnsql_params));
    assert(sp);
    sp->params=0;
    sp->qsl=0;
    return NULL;
}

mnsql_params *mnsql_params_init(mnsql_params *sp, char *sql, mnvariantList *params_list) {
    if (!sp) sp= mnsql_params_new();
    sp->qsl=sql;
    sp->params=params_list;
    return sp;
}

mnsql_params *mnsql_params_clean(mnsql_params *params) {
    cstring_free((void **) &params->qsl);
    mnvariantList_clean_free(&params->params);
    return params;
}

mndataset *mndataset_get_data(mndataset *dataset) {
    mnassert(dataset);
    mnassert(dataset->sql);
    mnassert(dataset->db);
    char* sql =mnsql_select(dataset->sql);
    mnrecordset_clean_free(&dataset->recordset);
    if (dataset->sql->filter){
        mnvariantList* params= mnfilter_vals(dataset->sql->filter);
        dataset->recordset=mndatabase_bind_params_and_get_data(dataset->db,params,sql);
    } else{
        dataset->recordset=mndatabase_get_data(dataset->db,sql);
    }
    return NULL;
}

size_t mndataset_insert(mndataset *dataset, mnvariantList *vals) {
    mnmetadata_list* metalist= dataset->tblsuper->meta_list;
    mncstringList* names_list = mncstringList_init(0);
    mnvariantList* vals_list = mnvariantList_init(0);
    for (size_t i = 0; i <metalist->count ; ++i) {
        mnmetadata* metadata= mnmetadata_list_item_at(metalist,i);
        if (!metadata->is_autoinc){
            mncstringList_add(names_list, str_cpy(metadata->name));
            mnvariantList_add(vals_list, mnvariantList_item_at(vals,i));
        }
    }
    char* sql=mnsql_sql_insert_with_params(names_list,dataset->tblsuper->table_name);
    mndatabase_bind_params_and_exec(dataset->db,vals_list,sql);
    size_t last_id=mndatabase_last_insert_id(dataset->db);
    mnvariantList_clean_free(&vals_list);
    mncstringList_clean_free(&names_list);
    return last_id;
}
