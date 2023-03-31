/*
 * mndatabase.c
 *
 *  Created on: ٠٣‏/٠٥‏/٢٠٢١
 *      Author: merhab
 */

#include "mndatabase.h"

mndatabase *mndatabase_new() {
    mndatabase *database = mnalloc(sizeof(mndatabase));
    mnassert(database);
    database->connection = 0;
    database->driver = UNKNOWN;
    return database;
}

mndatabase *mndatabase_init(mndatabase *database, db_drivers driver, void *connection_params) {
    if (!database) {
        database = mndatabase_new();
    }

    if (driver == SQLITE) {
        database->connection = mnsqlite_new(connection_params);
    } else if (driver == MYSQL) {
        //todo:mysql
    } else {
        assert(0);
    }
    database->driver = driver;
    return database;

}

mndatabase *mndatabase_clean(mndatabase *database) {
    if (database->driver == SQLITE) {
        mnsqlite_free(database->connection);
    } else if (database->driver == MYSQL) {

    } else {
        assert(0);
    }
    return database;
}

void mndatabase_free(mndatabase **database_hld) {
    mnfree(*database_hld);
    *database_hld = 0;
}

void mndatabase_free_v0(mndatabase *database) {
    mnfree(database);
}

char mndatabase_is_valid(mndatabase *self) {
    if (self->connection) return 1;
    return 0;
}

char mndatabase_exec(mndatabase *self, char *sql) {
    switch (self->driver) {
        case SQLITE:
            return mnsqlite_db_exec((sqlite3 *) self->connection, sql);
        case MYSQL:
            break;
        case UNKNOWN:
            assert(0);
    }
    return 1;
}

mnrecordset *mndatabase_get_data(mndatabase *self, const char *sql) {

    switch (self->driver) {
        case SQLITE:
            return mnsqlite_get_data((sqlite3 *) self->connection, (char *) sql);

        case MYSQL:
            return 0;

        case UNKNOWN:
            assert(0);
    }
    return 0;

}


//TODO:test mndatabase_bind_params_and_exec
 char mndatabase_bind_params_and_exec(mndatabase *db, mnvariantList *params, char *sql) {
    if (db->driver == SQLITE) {
        sqlite3 *sqlitedb = ((sqlite3 *) db->connection);
        return mnsqlie_bind_params_and_exec(sqlitedb,params,sql);
    } else if (db->driver == MYSQL) {

    } else {
        assert(0);
    }
    return 1;
}

//TODO: test mndatabase_last_insert_id
long long int mndatabase_last_insert_id(mndatabase *db) {
    if (db->driver == SQLITE) {
        sqlite3 *sqlitedb = ((sqlite3 *) db->connection);
        return mnsqlite_last_insert_id(sqlitedb);
    }
    return -1;
}


//TODO: mndatabase_insert_record
char mndatabase_insert_record(mndatabase *db, mnrecord *record, char *table_name, mnmetadata_list* meta) {
    //todo: inset an already in database record;
    mncstringList* flds = mnmetadata_list_fld_names_list(meta, 0, 0);
    char *sql = mnsql_sql_insert_with_params(flds,table_name);
    char ret = mndatabase_bind_params_and_exec(db, record, sql);
    cstring_free_v0(sql);
    mnmetadata *fld_meta;
    int i;
    for (i = 0; i < meta->count; ++i) {
        fld_meta = mnmetadata_list_item_at(meta, i);
        if (fld_meta->is_autoinc) break;
        else fld_meta = 0;
    }
    if (fld_meta) {
        long long int last_id = mndatabase_last_insert_id(db);
        mnvariant *var = mnvariantList_item_at(record, i);
        mnvariant_clean(var);
        mnvariant_init_big_int(var, last_id);
    }
    //mninteger l_id=mninteger_new_v2(last_id);
    mncstringList_clean_free(&flds);
    return ret;
}

//TODO: test mndatabase_update_record
char mndatabase_update_record(mndatabase *db, mnrecord *record, char *table_name, mnmetadata_list *meta) {
    mnmetadata *fld_meta;
    int i;
    for (i = 0; i < meta->count; ++i) {
        fld_meta = mnmetadata_list_item_at(meta, i);
        if (fld_meta->is_primary_key) break;
        else fld_meta = 0;
    }
    if (!fld_meta) assert(0);
    char *where_sql = cstring_concat_multi("WHERE %s = %d ",
                                           mnvariant_int(mnvariantList_item_at(record, i)));
    mncstringList* flds = mnmetadata_list_fld_names_list(meta, 0, 0);
    char *sql = (mnsql_sql_update_with_params(flds, table_name, where_sql));
    mncstringList_clean_free(&flds);
    char ret = mndatabase_bind_params_and_exec(db, record, sql);
    cstring_free_v0(where_sql);
    cstring_free_v0(sql);
    return ret;

}

char mndatabase_delete_record(mndatabase *db, mnrecord *record, char *table_name, mnmetadata_list *meta) {
    mnmetadata *fld_meta;
    int i;
    for (i = 0; i < meta->count; ++i) {
        fld_meta = mnmetadata_list_item_at(meta, i);
        if (fld_meta->is_primary_key) break;
        else fld_meta = 0;
    }
    if (!fld_meta) assert(0);
    char *where_sql = cstring_concat_multi("WHERE %s = %d ",
                                           mnvariant_int(mnvariantList_item_at(record, i)));
    char *sql = mnsql_sql_delete(table_name, where_sql);
    cstring_free_v0(where_sql);
    char res = mndatabase_exec(db, sql);
    cstring_free_v0(sql);
    return res;
}

mnrecordset *mndatabase_bind_params_and_get_data(mndatabase *db, mnvariantList *params, char *sql) {
    if (db->driver == SQLITE) {
        sqlite3 *sqlitedb = ((sqlite3 *) db->connection);
        return mnsqlie_bind_params_and_get_data(sqlitedb,params,sql);
    } else if (db->driver == MYSQL) {

    } else {
        assert(0);
    }
    return NULL;
}

mndatabase *mndatabase_init_sqlite(mndatabase *db, char *db_path) {
    mndatabase_init(db, SQLITE, mnsqlite_param_init_cpy(0, 0, 0, db_path));
    return db;
}

/*
 *
 * SQL_TABLE
 *
 */
