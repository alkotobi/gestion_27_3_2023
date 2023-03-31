//
// Created by merhab on 2023/3/18.
//
#include "mntable.h"

mntable * mntable_new() {
    mntable * tbl = (mntable *) mnalloc(sizeof(mntable) );
    assert(tbl);
    tbl->metadata =0;
    tbl->recordset=0;
    tbl->table_name =0;
    tbl->fld_names_list =0;
    tbl->db=0;
    tbl->msql =0;
    return tbl;
}

mntable * mntable_init(mntable *tbl, char *table_name, mnmetadata_list *meta_list,mndatabase* db) {
    tbl->table_name = table_name;
    tbl->metadata =meta_list;
    tbl->fld_names_list = mnmetadata_list_fld_names_list_cpy(meta_list, 0);
    tbl->db =db;
    tbl->msql= mnsql_init(0, db->driver, str_cpy(table_name),
                          mnsql_sql_fields(tbl->fld_names_list),
                          0, -1, -1);
    return tbl;
}

mntable * mntable_clean(mntable *tbl) {
    cstring_free_v0(tbl->table_name);
    mnrecordset_clean_free(&tbl->recordset);
    mnmetadata_list_clean_free((void **) &tbl->metadata);
    mncstringList_clean_free(& tbl->fld_names_list);
    mnsql_clean_free(&tbl->msql);
    return tbl;
}

void mntable_free(mntable **tbl_hld) {
    mnfree(*tbl_hld);
    *tbl_hld =0;
}




