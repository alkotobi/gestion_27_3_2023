#pragma once
#include "stdio.h"
#include "sqlite3.h"
#include "mnrecord.h"




#ifdef __cplusplus
extern "C"
{
#endif

#define MN_ROW         100
#define MN_OK            0
#define MN_DONE        101

typedef struct mnsqlite
{
    char *user;
    char *pass;
    char* db_path;
}mnsqlite_param;

mnsqlite_param *mnsqlite_param_new();

mnsqlite_param *mnsqlite_param_init_ref(mnsqlite_param *param, char *user, char *pass, char *db_path);//tested

mnsqlite_param *mnsqlite_param_init_cpy(mnsqlite_param *param, char *user, char *pass, char *db_path);//tested

mnsqlite_param *mnsqlite_param_clean(mnsqlite_param *param);

void mnsqlite_param_free(mnsqlite_param **param_hld);

void mnsqlite_param_free_v0(mnsqlite_param *param);

void mnsqlite_param_clean_free(mnsqlite_param **param_hld);

sqlite3 *mnsqlite_new(mnsqlite_param *param);

int mnsqlite_free(sqlite3* database);

char mnsqlite_db_exec(sqlite3* db,const char* sql);

long long int mnsqlite_last_insert_id(sqlite3* db);

mnrecordset * mnsqlite_get_data(sqlite3* db, char *sql);
char mnsqlie_bind_params_and_exec(sqlite3 *db, mnvariantList *params, char *sql);
mnrecordset* mnsqlie_bind_params_and_get_data(sqlite3 *db, mnvariantList *params, char *sql);
mnrecordset*  mnsqlite_getdata_v0(sqlite3_stmt* stmt );
void mnsqlite_bind_params(sqlite3_stmt* rds,mnvariantList *params);


#ifdef __cplusplus
}
#endif