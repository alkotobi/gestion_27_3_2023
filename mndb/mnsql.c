#include "mnsql.h"


mnsql *mnsql_new() {
    mnsql *sql = (mnsql *) mnalloc(sizeof(mnsql));
    mnassert(sql);
    sql->fields = 0;
    sql->filter = 0;
    sql->limit = 0;
    sql->offset = 0;
    sql->sql = 0;
    sql->sql_order_by = 0;
    sql->sql_rec_count = 0;
    //sql->sql_where = 0;
    sql->table_name = 0;
    return sql;
}


mnsql *
mnsql_init(mnsql *sql, db_drivers driver, char *table_name, char *fields, char *w_order_by, int limit, int offset) {
    if (!sql) {
        sql = mnsql_new();
    }
    sql->driver = driver;
    sql->fields = fields;
    sql->limit = limit;
    sql->offset = offset;
    //sql->sql = sql;
    sql->sql_order_by = w_order_by;
    //sql->sql_where = w_where;
    sql->table_name = table_name;
    //sql->filter = mnarray_init(mnarray_new());
    sql->sql = mnsql_select(sql);
    return sql;
}

mnsql *
mnsql_init_with_cstring_cpy(mnsql *sql, db_drivers driver, char *table_name, char *fields, char *w_order_by, int limit,
                            int offset) {
    return mnsql_init(sql, driver,
                      cstring_new_clone(table_name),
                      cstring_new_clone(fields),
                      cstring_new_clone(w_order_by),
                      limit,
                      offset);
}

mnsql *mnsql_clean(mnsql *msql) {
    if (!msql) return msql;
    if (msql->fields) {
        cstring_free((void **) &msql->fields);
        msql->fields = 0;
    }
    if (msql->filter) {
        mnfilter_clean_free(&(msql->filter));
    }
    if (msql->sql) {
        cstring_free((void **) &msql->sql);
        msql->sql = 0;
    }
    if (msql->sql_order_by) {
        cstring_free((void **) &msql->sql_order_by);
        msql->sql_order_by = 0;
    }
    if (msql->sql_rec_count) {
        cstring_free((void **) &msql->sql_rec_count);
        msql->sql_rec_count = 0;
    }
//    if (msql->sql_where) {
//        cstring_free((void **) &msql->sql_where);
//        msql->sql_where = 0;
//    }
    if (msql->table_name) {
        cstring_free((void **) &msql->table_name);
        msql->table_name = 0;
    }
    return msql;
}

void mnsql_free(mnsql **msql_hld) {
    mnfree(*msql_hld);
    *msql_hld = 0;
}

void mnsql_free_v0(mnsql *msql) {
    mnfree(msql);
}

void mnsql_clean_free(mnsql **msql_hld) {
    mnsql_clean(*msql_hld);
    mnsql_free(msql_hld);
}

// mnsql* mnsql_clone(mnsql* msql)
// {
//     mnsql* s = mnsql_new();
//     s->filters = mnarray_clone(msql->filters, (TFVarVar)char_clone);
//     s->limit = msql->limit;
//     s->offset = msql->offset;
//     s->sql = char_clone(msql->sql);
//     s->sql_order_by = char_clone((msql->sql_order_by));
//     s->table_name = char_clone(msql->table_name);
//     s->fields = char_clone(msql->fields);
//     s->sql_where = char_clone(msql->sql_where);
//     return s;
// }

// char mnsql_is_equal(mnsql* msql1, mnsql* msql2)
// {
//     return msql1->limit == msql2->limit &&
//             msql1->offset == msql2->offset &&
//             (mnarray_is_equal(msql1->filters, msql2->filters, (TFCharVarVar)char_is_equal)) &&
//             (char_is_equal(msql1->sql, msql2->sql)) &&
//             char_is_equal(msql1->sql_order_by, msql2->sql_order_by) &&
//             char_is_equal(msql1->table_name, msql2->table_name) &&
//             char_is_equal(msql1->fields, msql2->fields) &&
//             char_is_equal(msql1->sql_where, msql2->sql_where);
// }

char *mnsql_select(mnsql *msql) {
    mnassert(msql);
    if (msql->fields == 0 || msql->table_name == 0) {
        mnassert(0);
    }
    mnarray *trash = mnarray_init(mnarray_new());
    char *select_Sql = mnarray_add_cstring_ref(trash,
                                               cstring_concat_multi(" SELECT %s FROM %s ",
                                                                    msql->fields,
                                                                    msql->table_name));
//    char *where_sql;
//    if (msql->sql_where != 0 && (msql->sql_where[0] != 0)) {
//        where_sql = mnarray_add(trash,
//                                cstring_concat_multi(" WHERE %s ",
//                                                     msql->sql_where));
//    } else {
//        where_sql = mnarray_add(trash, cstring_new_clone(""));
//    }
    char *order_by;
    if (msql->sql_order_by != 0 && (msql->sql_order_by[0] != 0)) {
        order_by = mnarray_add(trash,
                               cstring_concat_multi(" ORDER BY %s ",
                                                    msql->sql_order_by));
    } else {
        order_by = mnarray_add(trash, cstring_new_clone(""));
    }
    char *limit_sql;
    if (msql->limit > 0) {
        limit_sql = mnarray_add(trash, cstring_concat_multi(
                " LIMIT %d OFFSET %d ",
                msql->limit,
                msql->offset));
    } else {
        limit_sql = mnarray_add(trash, cstring_new_clone(""));
    }
    char *filters="";
    if (msql->filter)
    filters = mncstringList_add(trash,mnfilter_create_with_params(msql->filter));
    if (!cstring_is_equal(filters,"")){
        filters = mncstringList_add(trash, cstring_new_concat_2(" WHERE ",filters));
    }
    if (msql->sql) {
        cstring_free((void **) &msql->sql);
    }
    if (msql->sql) cstring_free((void **) &msql->sql);
    msql->sql = cstring_concat_multi("%s%s%s%s", select_Sql,
                                      filters, order_by, limit_sql);
    if (msql->sql_rec_count) cstring_free((void **) &msql->sql_rec_count);
    msql->sql_rec_count = cstring_concat_multi("SELECT COUNT() as count from %s %s ",
                                               msql->table_name, filters);
    mnarray_clean_cstring(trash);
    mnarray_free(&trash);
    return msql->sql;
}

void mnsql_add_filter(mnsql *msql,  enum mnlogic_op log_oper, char *field_name,  enum mncomp_op comp_op) {
    mnfilter* flt = mnfilter_init(0,
                                  log_oper, field_name, comp_op, NULL);
    msql->filter = flt;
}

void mnsql_set_order(mnsql *msql, char *w_order) {
    if (msql->sql_order_by) {
        cstring_free((void **) &msql->sql_order_by);
    }
    msql->sql_order_by = ((w_order));
}

void mnsql_set_order_cpy(mnsql *msql, char *w_order) {
    mnsql_set_order(msql, cstring_new_clone(w_order));
}

void mnsql_set_limit(mnsql *msql, int limit, int offset) {
    msql->limit = limit;
    msql->offset = offset;
}

void mnsql_set_fields(mnsql *msql, char *fields) {
    if (msql->fields) {
        cstring_free((void **) &msql->fields);
    }
    msql->fields = (fields);
}

void mnsql_set_fields_cpy(mnsql *msql, char *fields) {
    mnsql_set_fields(msql, cstring_new_clone(fields));
}

void mnsql_set_table(mnsql *msql, char *table_name) {
    if (msql->table_name) {
        cstring_free((void **) &msql->table_name);
    }
    msql->table_name = ((table_name));
}

void mnsql_set_table_cpy(mnsql *msql, char *table_name) {
    mnsql_set_table(msql, cstring_new_clone(table_name));
}

void mnsql_clear_filters(mnsql *msql) {
    mnfilter_clean_free(&msql->filter);
}

char *mnsql_sql(mnsql *sql) {
    return sql->sql;
}

char *mnsql_create_table(mnarray *var_list, mncstringList *field_names, char *table_name) {
    size_t i = 0;
    mncstringList *trash = mncstringList_init(mncstringList_new());
    char *str = mncstringList_add(trash,
                                  cstring_concat_multi("CREATE TABLE IF NOT EXISTS '%s%s",
                                                       table_name, "' ("));
    if (cstring_is_equal(field_names->array[0],
                         cstring_new_clone("ID"))) {
        str = mncstringList_add(trash, cstring_new_from_concat(2, str, "'ID' INTEGER PRIMARY KEY AUTOINCREMENT,"));
        i = 1;
    }


    for (; i < field_names->count; i++) {

        mnvariant *fld = var_list->array[i];
        mntypes type = fld->data_type;
        char *strType;
        switch (type) {
            case CString:
                strType = cstring_new_clone("TEXT");
                break;
            case Int:
                strType = cstring_new_clone("int");
                break;
            case Double:
                strType = cstring_new_clone("double");
                break;
            default:
                assert(0);
        }


        char *str1 = mncstringList_add(trash, cstring_concat_multi("'%s%s%s", field_names->array[i], "' ", strType));
        cstring_free((void **) &strType);
        if (i != field_names->count - 1) {
            str1 = mncstringList_add(trash, cstring_new_from_concat(2, str1, ","));
        }
        str = mncstringList_add(trash, cstring_new_from_concat(2, str, str1));
    }

    str = cstring_new_from_concat(2, str, ");");
    mncstringList_clean_free(&trash);
    return str;

}

char *mnsql_create_table_v0(char *table_name, mnmetadata_list *fields) {
    TRASH;
    char *cst = "";
    for (size_t i = 0; i < fields->count; ++i) {
        mnmetadata *fld = mnmetadata_list_item_at(fields, i);
        mntypes type = fld->type;
        char *strType;
        switch (type) {
            case CString:
                strType = cstring_new_clone("TEXT");
                break;
            case Int:
                strType = cstring_new_clone("INTEGER");
                break;
            case Double:
                strType = cstring_new_clone("double");
                break;
            case Big_int:
                strType = cstring_new_clone("INTEGER");
                break;
            default:
                assert(0);
        }
        cst = $(cstring_concat_multi("%s %s %s ",cst,fld->name,strType));
        if (fld->is_unique) { cst =$(cstring_new_concat_2(cst , " UNIQUE ")); }
        if (fld->default_val) {
            if (fld->default_val->data_type != CString) {
                cst = $(cstring_new_from_concat(3,cst," default ", mnvariant_to_new_cstring(fld->default_val)));
            } else {
                cst = $(cstring_new_from_concat(4, cst, " default '", mnvariant_to_new_cstring(fld->default_val), "' "));
            }
        }
        if (fld->must_not_nul) {
            cst = $(cstring_new_concat_2(cst, " not null "));
        }
        if (fld->is_autoinc ){
            cst = $(cstring_concat_multi("%s    primary key autoincrement",cst,fld->name));
        }
        if (fld->is_primary_key && !fld->is_autoinc){
            cst = $(cstring_concat_multi(" %s   primary key ",cst,fld->name));
        }
        if (i<fields->count-1){
            cst = $(cstring_new_concat_2(cst," , "));
        }
    }
    char *str = cstring_concat_multi("CREATE TABLE IF NOT EXISTS '%s%s%s%s",
                                       table_name, "' (",cst,");");
    EMPTY_TRASH;
    return str;
}

char *mnsql_sql_fields(mncstringList *field_names) {
    //todo:redesign
    char *str = mncstringList_concat(field_names, ",");
    size_t count = cstring_count(str);
    str[count - 1] = 0;
    return str;

}

char *mnsql_sql_binding_params(mncstringList *names) {
    //todo:redesign
    char *sql = "";
    mncstringList *trash = mncstringList_init(mncstringList_new());
    for (int i = 0; i < names->count; i++) {
        sql = mncstringList_add(trash, cstring_new_concat_2(sql, ":"));
        sql = mncstringList_add(trash, cstring_new_concat_2(sql, mncstringList_item_at(names, i)));
        if (i != names->count - 1)
            sql = mncstringList_add(trash, cstring_new_concat_2(sql, ","));

    }
    //sql->string[sql->last_char_pos]=' ';
    sql = cstring_new_clone(sql);
    mncstringList_clean_free(&trash);
    return sql;
}

char *mnsql_sql_insert_with_params(mncstringList *names, char *table_name) {
    // INSERT INTO TABLE_NAME(fld,..) VALUES(?,...)
    mncstringList *trash = mncstringList_init(mncstringList_new());
    char *str1 = mncstringList_add(trash, mnsql_sql_fields(names));
    char *str2 = mncstringList_add(trash, mnsql_sql_binding_params(names));
    char *sql = cstring_concat_multi(
            "INSERT INTO %s(%s) VALUES(%s)",
            table_name, str1, str2);
    mncstringList_clean_free(&trash);
    return sql;
}


char *mnsql_sql_update_with_params(mncstringList *names, char *table_name, char *where_close) {
    /*
UPDATE table_name
SET column1 = value1, column2 = value2, ...
WHERE condition;
     */
    mncstringList *trash = mncstringList_init(mncstringList_new());
    char *str = mncstringList_add(trash, cstring_concat_multi("UPDATE %s SET ", table_name));
    for (int i = 0; i < names->count; i++) {
        char *s;//=fld->name->string;
        //s=cstring_concat_multi("%s = :%s", mncstringList_item_at(names,i),mncstringList_item_at(names,i));
        if (i == names->count - 1) {
            s = mncstringList_add(trash, cstring_concat_multi("%s = :%s",
                                                              mncstringList_item_at(names, i),
                                                              mncstringList_item_at(names, i)));
        } else {
            s = mncstringList_add(trash, cstring_concat_multi("%s = :%s ,",
                                                              mncstringList_item_at(names, i),
                                                              mncstringList_item_at(names, i)));
        }
        str = mncstringList_add(trash, cstring_new_concat_2(str, s));

    }
    if (where_close) {
        str = mncstringList_add(trash, cstring_concat_multi("%s WHERE %s", str, where_close));
    }
    for (size_t i = 0; i < trash->count - 1; i++) {
        free(mncstringList_item_at(trash, i));
    }
    mncstringList_free(&trash);
    return str;
}

char *mnsql_sql_delete(char *table_name, char *where_close) {
    return cstring_new_from_concat(4, "DELETE  FROM ", table_name, " where ", where_close);
}

char *mnsql_create_table_v1(mnmeta_super* tbl) {
    return mnsql_create_table_v0(tbl->table_name,tbl->meta_list);
}

mnsql *mnsql_limit_offset(mnsql *sql, size_t limit, size_t offset) {
    sql->limit=limit;
    sql->offset = offset;
    return sql;
}

mnsql *mnsql_orderby(mnsql *sql, mnmetadata meta, db_order_dir dir) {
   char* str;
    switch (dir) {
        case DESC:
            str = "DESC";
            break;
        case ASC:
            str = "ASC";
            break;
        default:
            mnassert(0);
    }
    cstring_free((void **) &sql->sql_order_by);
    sql->sql_order_by=cstring_concat_multi(" %s %s ",meta.name,str);
    return sql;
}

mnsql *
mnsql_init_v0(mnsql *sql, db_drivers driver, char *table_name, mnmetadata_list *meta_list, char only_generated) {
    return mnsql_init(sql,driver,table_name,
                      mnsql_sql_fields(
                              mnmetadata_list_fld_names_list(
                                      meta_list, only_generated, 0)
                                      ),
                      0,0,0);
}




