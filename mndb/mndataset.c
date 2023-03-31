//
// Created by merhab on 2023/3/26.
//

#include "mndataset.h"

mndataset *mndataset_new() {
    mndataset *d = (mndataset *) mnalloc(sizeof(mndataset));
    mnassert(d);
    d->recordset = 0;
    d->tblsuper = 0;
    return d;
}

mndataset *mndataset_init(mndataset *dataset, tbl_super *tblsuper, mndatabase *db, mnsql *msql) {
    if (!dataset) dataset = mndataset_new();
    dataset->tblsuper = tblsuper;
    dataset->db = db;
    dataset->sql = msql;
    dataset->recordset = mnrecordset_init(0);
    return dataset;
}

mndataset *mndataset_clean_recordset(mndataset *dataset) {
    mnrecordset_clean_free(&dataset->recordset);
    return dataset;
}

void mndataset_free(mndataset **dataset_hld) {
    mnfree(*dataset_hld);
    *dataset_hld = 0;
}

char mndataset_create_table(mndataset *dataset) {
    char *sql = mnsql_create_table_v0(dataset->tblsuper->table_name, dataset->tblsuper->meta_list);
    char ret = mndatabase_exec(dataset->db, sql);
    cstring_free_v0(sql);
    return ret;
}

mnsql_params *mnsql_params_new() {
    mnsql_params *sp = (mnsql_params *) mnalloc(sizeof(mnsql_params));
    assert(sp);
    sp->params = 0;
    sp->qsl = 0;
    return NULL;
}

mnsql_params *mnsql_params_init(mnsql_params *sp, char *sql, mnvariantList *params_list) {
    if (!sp) sp = mnsql_params_new();
    sp->qsl = sql;
    sp->params = params_list;
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
    char *sql = mnsql_select(dataset->sql);
    mnrecordset_clean_free(&dataset->recordset);
    if (dataset->sql->filter) {
        mnvariantList *params = mnfilter_vals(dataset->sql->filter);
        dataset->recordset = mndatabase_bind_params_and_get_data(dataset->db, params, sql);
    } else {
        dataset->recordset = mndatabase_get_data(dataset->db, sql);
    }
    return NULL;
}

size_t mndataset_insert(mndataset *dataset, mnvariantList *vals) {
    mnmetadata_list *metalist = dataset->tblsuper->meta_list;
    mncstringList *names_list = mncstringList_init(0);
    mnvariantList *vals_list = mnvariantList_init(0);
    for (size_t i = 0; i < metalist->count; ++i) {
        mnmetadata *metadata = mnmetadata_list_item_at(metalist, i);
        if (!metadata->is_autoinc) {
            mncstringList_add(names_list, (metadata->name));
            mnvariantList_add(vals_list, mnvariantList_item_at(vals, i));
        }
    }
    char *sql = mnsql_sql_insert_with_params(names_list, dataset->tblsuper->table_name);
    mndatabase_bind_params_and_exec(dataset->db, vals_list, sql);
    size_t last_id = mndatabase_last_insert_id(dataset->db);
    mnvariantList_free(&vals_list);
    mncstringList_free(&names_list);
    return last_id;
}

size_t mndataset_insert_v0(mndataset *dataset, record_super *record) {
    size_t last_id = mndataset_insert(dataset, &(record->var_list));
    int64_t ind = tbl_super_autoinc_index(dataset->tblsuper);
    if (ind >= 0) {
        record->var_list_set_field_at_clean_ex((void *) &record->var_list, VAR_BI(last_id), (char) ind);
    }
    mnarray_add(dataset->recordset, &(record->var_list));
    return 0;
}

size_t mndataset_get_primary_key_field_ind(mndataset *dataset) {
    for (size_t i = 0; i < dataset->tblsuper->meta_list->count; ++i) {
        mnmetadata *meta = mnmetadata_list_item_at(dataset->tblsuper->meta_list, i);
        if (meta->is_primary_key) return i;
    }
    return -1;
}

mnvariant *mndataset_get_primary_key_value(mndataset *dataset, record_super *record) {
    size_t ind = mndataset_get_primary_key_field_ind(dataset);
    if (ind == -1) mnassert(0);
    mnvariant *val = mnarray_item_at(&record->var_list, ind);
    return val;
}

char mndataset_update(mndataset *dataset, record_super *record) {
    //todo: update only changed fields

    struct mnfilter *filter = mnfilter_init(0, AND, mndataset_get_primary_key_filed_name(dataset), EQ,
                                            mndataset_get_primary_key_value(dataset, record));
    char *str = mnfilter_create_with_params(filter);
    //char *where = cstring_new_concat_2(" where ", str);
    mncstringList *list = mnmetadata_list_fld_names_list_cpy(dataset->tblsuper->meta_list, 0);
    char *sql = mnsql_sql_update_with_params(list, dataset->tblsuper->table_name, str);
    mnvariantList *filter_vals = mnfilter_vals(filter);
    mnvariantList *vals = mnarray_concat_to_new_array(&record->var_list, filter_vals);
    char ret = mndatabase_bind_params_and_exec(dataset->db, vals, sql);

    cstring_free((void **) &sql);
    mnvariantList_free(&filter_vals);
    mnfilter_free(&filter);
    mncstringList_clean_free(&list);
    cstring_free((void **) &str);
    //cstring_free((void **) &where);
    mnvariantList_free(&vals);
    return ret;
}

mncstringList *mndatset_get_fields_names_list(mndataset *dataset, char only_generated) {
    return mnmetadata_list_fld_names_list_cpy(dataset->tblsuper->meta_list, only_generated);
}

size_t mndataset_get_autoinc_field_ind(mndataset *dataset) {
    for (size_t i = 0; i < dataset->tblsuper->meta_list->count; ++i) {
        mnmetadata *meta = mnmetadata_list_item_at(dataset->tblsuper->meta_list, i);
        if (meta->is_autoinc) return i;
    }
    return -1;
}

char *mndataset_get_primary_key_filed_name(mndataset *dataset) {
    size_t ind = mndataset_get_primary_key_field_ind(dataset);
    if (ind == -1) mnassert(0);
    mnmetadata *meta = mnarray_item_at(dataset->tblsuper->meta_list, ind);
    return meta->name;
}
