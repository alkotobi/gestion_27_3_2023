#include "mnsqlite.h"

mnsqlite_param *mnsqlite_param_new()
{
    mnsqlite_param *param =(mnsqlite_param*)mnalloc(sizeof(mnsqlite_param));
    mnassert(param);
    param->pass=0;
    param->user=0;
    return param;
}

mnsqlite_param *mnsqlite_param_init_ref(mnsqlite_param *param, char *user, char *pass, char *db_path)
{
    if (!param)
    {
        param = mnsqlite_param_new();
    }
    param->pass=pass;
    param->user=user;
    param->db_path = db_path;
    return param;
    
}

mnsqlite_param *mnsqlite_param_init_cpy(mnsqlite_param *param, char *user, char *pass, char *db_path)
{
    return mnsqlite_param_init_ref(param, cstring_new_clone(user), cstring_new_clone(pass), str_cpy(db_path));
}

mnsqlite_param *mnsqlite_param_clean(mnsqlite_param *param)
{
    cstring_free_v0(param->pass);
    param->pass=0;
    cstring_free_v0(param->user);
    param->user=0;
    return param;
}

void mnsqlite_param_free(mnsqlite_param **param_hld)
{
    mnsqlite_param_free_v0(*param_hld);
    *param_hld=0;
}

void mnsqlite_param_free_v0(mnsqlite_param *param)
{
    mnfree(param);
}

void mnsqlite_param_clean_free(mnsqlite_param **param_hld)
{
    mnsqlite_param_clean(*param_hld);
    mnsqlite_param_free(param_hld);
}

sqlite3 *mnsqlite_new(mnsqlite_param *param)
{
    mnassert(param);
    sqlite3 *db=0;
    int res;
        res = sqlite3_open(param->db_path,&db);
        if(res!=MN_OK){
            mnassert(0);
            return 0;
        }
    return db;
}


int mnsqlite_free(sqlite3* database)
{
    int res =sqlite3_close(database);
    return res;
}

char mnsqlite_db_exec(sqlite3* db,const char* sql){
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        sqlite3_close(db);
        mnassert(0);
        return 0;
    }
    sqlite3_free(err_msg);
    return 1;
}

long long int mnsqlite_last_insert_id(sqlite3* db){
    return  sqlite3_last_insert_rowid(db);
}


mnrecordset*  mnsqlite_getdata_v0(sqlite3_stmt* stmt ){
    mnrecordset* recordset = mnrecordset_init(0);
    int col_count=sqlite3_column_count(stmt);
    while(sqlite3_step(stmt)==SQLITE_ROW){
        mnvariantList* record= mnvariantList_init(mnvariantList_new());
        for(int i=0;i<col_count;i++){

            if(sqlite3_column_type(stmt,i)==SQLITE_INTEGER){
                mnvariant* field=mnvariant_init_int(mnvariant_new(),sqlite3_column_int(stmt,i));
                mnvariantList_add(record,field);
                //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
            }else if(sqlite3_column_type(stmt,i)==SQLITE_TEXT){
                mnvariant* field=mnvariant_init_cstring_cpy(mnvariant_new(),(char*)sqlite3_column_text(stmt,i));
                mnvariantList_add(record,field);
                //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
            }else if(sqlite3_column_type(stmt,i)==SQLITE_FLOAT){
                mnvariant* field=mnvariant_init_double(mnvariant_new(),sqlite3_column_double(stmt,i));
                mnvariantList_add(record,field);
                //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
            }
            else if(sqlite3_column_type(stmt,i)==SQLITE_NULL){
                mnvariant* field=mnvariant_init_null();
                mnvariantList_add(record,field);
                //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
            }
        }
        mnrecordset_add(recordset,record);
    }
}

 mnrecordset * mnsqlite_get_data(sqlite3* db, char *sql)
{
            sqlite3_stmt* stmt;
            const char* tail ;
            mnrecordset* recordset=0;
            int res=sqlite3_prepare_v2(db,sql,-1,&stmt,&tail);
            if(res!=SQLITE_OK){
                mnassert(0);
                return recordset ;
            }
            recordset = mnrecordset_init(0);
            int col_count=sqlite3_column_count(stmt);
            while(sqlite3_step(stmt)==SQLITE_ROW){
                mnvariantList* record= mnvariantList_init(mnvariantList_new());
                for(int i=0;i<col_count;i++){

                    if(sqlite3_column_type(stmt,i)==SQLITE_INTEGER){
                        mnvariant* field=mnvariant_init_int(mnvariant_new(),sqlite3_column_int(stmt,i));
                        mnvariantList_add(record,field);
                        //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
                    }else if(sqlite3_column_type(stmt,i)==SQLITE_TEXT){
                        mnvariant* field=mnvariant_init_cstring_cpy(mnvariant_new(),(char*)sqlite3_column_text(stmt,i));
                        mnvariantList_add(record,field);
                        //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
                    }else if(sqlite3_column_type(stmt,i)==SQLITE_FLOAT){
                        mnvariant* field=mnvariant_init_double(mnvariant_new(),sqlite3_column_double(stmt,i));
                        mnvariantList_add(record,field);
                        //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
                    }
                    else if(sqlite3_column_type(stmt,i)==SQLITE_NULL){
                        mnvariant* field=mnvariant_init_null();
                        mnvariantList_add(record,field);
                        //mncstringList_add_clone(tbl->names,sqlite3_column_name(stmt,i));
                    }
                }
                mnrecordset_add(recordset,record);
            }
            sqlite3_finalize(stmt);
            return recordset;
        
}
void mnsqlite_bind_params(sqlite3_stmt* rds,mnvariantList *params){
    int j = 1;
    for (TLint i = 0; i < params->count; i++) {
        mnvariant *field = mnvariantList_item_at(params, i);
        int val;
        const char *text;
        switch (field->data_type) {
            case CString:
                text = mnvariant_cstring_ret_ref(field);
                sqlite3_bind_text(rds, j, text, -1, 0);
                break;
            case Int:
                val = (mnvariant_int(field));
                sqlite3_bind_int(rds, j, val);
                break;
            case Double:
                sqlite3_bind_double(rds, j, mnvariant_double(field));
                break;
            case Big_int:
                sqlite3_bind_int64(rds,j, mnvariant_big_int(field));
                break;
            default:
                assert(0);

            case Null:
                sqlite3_bind_null(rds,j);
                break;
        }
        j++;
    }
}
char mnsqlie_bind_params_and_exec(sqlite3 *db, mnvariantList *params, char *sql) {
    sqlite3 *sqlitedb =  db;
    sqlite3_stmt *rds;
    const char *tail;
    int res;
    res = sqlite3_prepare_v2(sqlitedb, sql, -1, &rds, &tail);
    if (res != MN_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlitedb));
        sqlite3_finalize(rds);
        //mnassert(0);
        return 0;
    }
    mnsqlite_bind_params(rds,params);
    res = sqlite3_step(rds);
    if (res == MN_DONE) {
        sqlite3_finalize(rds);
        //sqlite3_last_insert_rowid(sqlitedb);
        return 1;
    } else{
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlitedb));
        sqlite3_finalize(rds);
        //mnassert(0);
        return 0;
    }

}

mnrecordset *mnsqlie_bind_params_and_get_data(sqlite3 *db, mnvariantList *params, char *sql) {
    sqlite3 *sqlitedb =  db;
    sqlite3_stmt *rds;
    const char *tail;
    int res;
    res = sqlite3_prepare_v2(sqlitedb, sql, -1, &rds, &tail);
    if (res != MN_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlitedb));
        sqlite3_finalize(rds);
        mnassert(0);
    }
    mnsqlite_bind_params(rds,params);
    mnrecordset* r =mnsqlite_getdata_v0(rds);
    sqlite3_finalize(rds);
    return r;
}
