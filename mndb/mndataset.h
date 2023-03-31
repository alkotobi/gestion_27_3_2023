//
// Created by merhab on 2023/3/26.
//

#pragma once
#include "mnmetadata.h"
#include "mnrecord.h"
#include "mnsql.h"
#include "mnfilter.h"
#include "mndatabase.h"
#include "mntest.h"
typedef struct {
    char* qsl;
    mnvariantList* params;
}mnsql_params;
mnsql_params* mnsql_params_new();
mnsql_params* mnsql_params_init(mnsql_params* sp, char* sql,mnvariantList* params_list);
mnsql_params* mnsql_params_clean(mnsql_params* params);
typedef struct {
    tbl_super* tblsuper;
    mnrecordset * recordset;
    mndatabase* db;
    mnsql* sql;
}mndataset;
mndataset* mndataset_new();//tested
mndataset *mndataset_init(mndataset *dataset, tbl_super *tblsuper, mndatabase *db, mnsql *msql);//tested
mndataset* mndataset_clean_recordset(mndataset* dataset);
void mndataset_free(mndataset** dataset_hld);
char mndataset_create_table(mndataset* dataset);//tested
mndataset *mndataset_get_data(mndataset *dataset);//tested
size_t mndataset_insert(mndataset* dataset,mnvariantList * vals);//tested
size_t mndataset_insert_v0(mndataset* dataset,record_super * record);//tested
char mndataset_update(mndataset* dataset, record_super* record);
size_t mndataset_get_primary_key_field_ind(mndataset* dataset);
size_t mndataset_get_autoinc_field_ind(mndataset* dataset);
mncstringList* mndatset_get_fields_names_list(mndataset* dataset,char only_generated);
char* mndataset_get_primary_key_filed_name(mndataset* dataset);



