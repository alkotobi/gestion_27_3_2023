/*
 * mndatabase.h
 *
 *  Created on: ٠٣‏/٠٥‏/٢٠٢١
 *      Author: merhab
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "mnsql.h"
#include "mnsqlite.h"
#include <stdio.h>
//#include "mntable.h"
#include "mnrecord.h"
#include "mncstringList.h"
#include "mn_db_const.h"




typedef struct{
    db_drivers driver;
    void* connection;
}mndatabase;


void mndatabase_free(mndatabase **database_hld);
void mndatabase_free_v0(mndatabase *database);
char mndatabase_is_valid(mndatabase* self);
char mndatabase_exec(mndatabase* self,char* sql);
long long int mndatabase_last_insert_id(mndatabase* db);
char mndatabase_insert_record(mndatabase *db, mnrecord *record, char *table_name, mnmetadata_list* meta);
char mndatabase_update_record(mndatabase *db, mnrecord *record, char *table_name, mnmetadata_list *meta);
char mndatabase_delete_record(mndatabase *db, mnrecord *record, char *table_name, mnmetadata_list *meta);
mnrecordset * mndatabase_get_data(mndatabase* self, const char* sql);
mndatabase* mndatabase_new();
mndatabase *mndatabase_init(mndatabase *database, db_drivers driver, void *connection_params);//tested
mndatabase* mndatabase_init_sqlite(mndatabase* db,char* db_path);//tested
mndatabase* mndatabase_clean(mndatabase* database);
static char mndatabase_bind_params_and_exec(mndatabase *db, mnvariantList *params, char *sql);
mnrecordset* mndatabase_bind_params_and_get_data(mndatabase *db, mnvariantList *params, char *sql);
#ifdef __cplusplus
}
#endif


