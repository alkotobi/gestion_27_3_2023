//
// Created by merhab on 2023/3/26.
//

#include "mndataset.h"

mndataset *mndataset_new() {
    mndataset *d = (mndataset *) mnalloc(sizeof(mndataset));
    mnassert(d);
    d->recordset = 0;
    d->meta_super = 0;
    return d;
}

mndataset *mndataset_init(mndataset *dataset, mnmeta_super *meta_super, mndatabase *db, mnsql *msql) {
    if (!dataset) dataset = mndataset_new();
    dataset->meta_super = meta_super;
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
    char *sql = mnsql_create_table_v0(dataset->meta_super->table_name, dataset->meta_super->meta_list);
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
    mnmetadata_list *metalist = dataset->meta_super->meta_list;
    mncstringList *names_list = mncstringList_init(0);
    mnvariantList *vals_list = mnvariantList_init(0);
    for (size_t i = 0; i < metalist->count; ++i) {
        mnmetadata *metadata = mnmetadata_list_item_at(metalist, i);
        if (!metadata->is_autoinc) {
            mncstringList_add(names_list, (metadata->name));
            mnvariantList_add(vals_list, mnvariantList_item_at(vals, i));
        }
    }
    char *sql = mnsql_sql_insert_with_params(names_list, dataset->meta_super->table_name);
    mndatabase_bind_params_and_exec(dataset->db, vals_list, sql);
    size_t last_id = mndatabase_last_insert_id(dataset->db);
    mnvariantList_free(&vals_list);
    mncstringList_free(&names_list);
    return last_id;
}

size_t mndataset_insert_v0(mndataset *dataset, mnrecord_super *record) {
    size_t last_id = mndataset_insert(dataset, &(record->var_list));
    int64_t ind = mnmeta_super_autoinc_index(dataset->meta_super);
    if (ind >= 0) {
        record->var_list_set_field_at_clean_ex((void *) &record->var_list, VAR_BI(last_id), (char) ind);
    }
    mnarray_add(dataset->recordset, &(record->var_list));
    return 0;
}


mnvariant *mndataset_get_primary_key_value(mndataset *dataset, mnrecord_super *record, char is_by_clone_val) {
    size_t ind = mnmeta_super_get_primary_key_field_ind(dataset->meta_super);
    if (ind == -1) mnassert(0);
    if (is_by_clone_val)
        return mnvariant_clone_v0(mnarray_item_at(&record->var_list, ind));
    else return mnarray_item_at(&record->var_list, ind);

}


char mndataset_update(mndataset *dataset, mnrecord_super *record) {
    mnvariantList* list_dirty_indexes= mnrecord_super_new_list_dirty_indexes(record);
    mnvariantList* list_dirty_values = mnrecord_super_new_list_dirty_values(record, 0);
    mncstringList* list_dirty_names= mnmeta_super_get_fields_names_list_by_indexes(dataset->meta_super,0,list_dirty_indexes,0);
    struct mnfilter *
    filter = mnfilter_init(0,
                           AND,
                           mnmeta_super_get_primary_key_filed_name(dataset->meta_super, 0),
                           EQ,
                           mndataset_get_primary_key_value(dataset, record, 0));
    char *str = mnfilter_create_with_params(filter);
    //char *where = cstring_new_concat_2(" where ", str);
    //mncstringList *list = mnmetadata_list_fld_names_list(dataset->meta_super->meta_list, 0, 0);
    char *sql = mnsql_sql_update_with_params(list_dirty_names, dataset->meta_super->table_name, str);
    mnvariantList *filter_vals = mnfilter_vals(filter);
    //mnvariantList *vals = mnarray_concat_to_new_array(&record->var_list, filter_vals);
    char ret = mndatabase_bind_params_and_exec(dataset->db, list_dirty_values, sql);
    mnrecord_super_set_dirty_items_in_indexes(record,list_dirty_indexes,0);
    cstring_free((void **) &sql);
    mnvariantList_free(&filter_vals);
    mnfilter_free(&filter);
    //mncstringList_clean_free(&list);
    cstring_free((void **) &str);
    //cstring_free((void **) &where);
    //mnvariantList_free(&vals);
    mnvariantList_clean_free(&list_dirty_indexes);
    mnvariantList_free(&list_dirty_values);
    mncstringList_free(&list_dirty_names);
    return ret;
}

char mndataset_update_records(mndataset *dataset, mnrecordset *records) {
//    mnvariantList* list_dirty_indexes= mnrecord_super_new_list_dirty_indexes(record);
//    mnvariantList* list_dirty_values = mnrecord_super_new_list_dirty_values(record, 0);
//    mncstringList* list_dirty_names= mnmeta_super_get_fields_names_list_by_indexes(dataset->meta_super,0,list_dirty_indexes,0);
//    struct mnfilter *
//            filter = mnfilter_init(0,
//                                   AND,
//                                   mnmeta_super_get_primary_key_filed_name(dataset->meta_super, 0),
//                                   EQ,
//                                   mndataset_get_primary_key_value(dataset, record, 0));
//    char *str = mnfilter_create_with_params(filter);
//    //char *where = cstring_new_concat_2(" where ", str);
//    //mncstringList *list = mnmetadata_list_fld_names_list(dataset->meta_super->meta_list, 0, 0);
//    char *sql = mnsql_sql_update_with_params(list_dirty_names, dataset->meta_super->table_name, str);
//    mnvariantList *filter_vals = mnfilter_vals(filter);
//    //mnvariantList *vals = mnarray_concat_to_new_array(&record->var_list, filter_vals);
//    char ret = mndatabase_bind_params_and_exec(dataset->db, list_dirty_values, sql);
//    mnrecord_super_set_dirty_items_in_indexes(record,list_dirty_indexes,0);
//    cstring_free((void **) &sql);
//    mnvariantList_free(&filter_vals);
//    mnfilter_free(&filter);
//    //mncstringList_clean_free(&list);
//    cstring_free((void **) &str);
//    //cstring_free((void **) &where);
//    //mnvariantList_free(&vals);
//    mnvariantList_clean_free(&list_dirty_indexes);
//    mnvariantList_free(&list_dirty_values);
//    mncstringList_free(&list_dirty_names);
//    return ret;
}






