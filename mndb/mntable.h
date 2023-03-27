//
// Created by merhab on 2023/3/18.
//
#pragma once
#include "mnsystem.h"
#include "mnmetadata.h"
#include "mnrecord.h"
#include "mncstringList.h"
#include "mndatabase.h"
#include "mnsql.h"
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
typedef struct {
    char* table_name;
    mnmetadata_list* metadata;
    mnrecordset* recordset;
    mncstringList* fld_names_list;
    mnsql* msql;
    mndatabase* db;
}mntable;

mntable * mntable_new();
mntable * mntable_init(mntable *tbl, char* table_name, mnmetadata_list* meta_list,mndatabase* db);
mntable * mntable_clean(mntable *tbl);
void mntable_free(mntable **tbl_hld);

#ifdef __cplusplus
}
#endif