#pragma once

#include "mncstringList.h"
#include "mnvariant.h"
#include "mn_db_const.h"
#include "mnmetadata.h"
#include "mnfilter.h"
#include "mnmeta_super.h"



typedef struct mnsql mnsql;
struct mnsql {
    db_drivers driver;
    char* table_name;
    char* fields;
    char* sql_order_by;
    //char* sql_where;
    mnfilter * filter;
    int limit;
    int offset;
    char* sql;
    char* sql_rec_count;
};

mnsql* mnsql_new(void);
mnsql *
mnsql_init(mnsql *sql, db_drivers driver, char *table_name, char *fields, char *w_order_by, int limit, int offset);
mnsql *mnsql_init_v0(mnsql *sql, db_drivers driver, char *table_name, mnmetadata_list *meta_list, char only_generated);
mnsql *
mnsql_init_with_cstring_cpy(mnsql *sql, db_drivers driver, char *table_name, char *fields, char *w_order_by, int limit,
                            int offset);
mnsql* mnsql_clean(mnsql* msql);
void mnsql_free(mnsql** msql_hld);
void mnsql_free_v0(mnsql *msql);
void mnsql_clean_free(mnsql** msql_hld);
mnsql* mnsql_clone(mnsql* msql);
char mnsql_is_equal(mnsql* msql1, mnsql* msql2);
char* mnsql_select(mnsql* msql);
void mnsql_add_filter(mnsql *msql, enum mnlogic_op log_oper, char *field_name, enum mncomp_op comp_op);
void mnsql_set_order(mnsql* msql,  char* w_order);
void mnsql_set_order_cpy(mnsql* msql, char* w_order);
void mnsql_set_limit(mnsql* msql, int limit, int offset);
void mnsql_set_fields(mnsql* msql,  char* fields);
void mnsql_set_fields_cpy(mnsql* msql, char* fields);
void mnsql_set_table(mnsql* msql,  char* table_name);
void mnsql_set_table_cpy(mnsql* msql, char* table_name);
void mnsql_clear_filters(mnsql* msql);
char* mnsql_sql(mnsql* sql);
char* mnsql_create_table(mnarray* var_list,mncstringList* field_names,char* table_name);
char* mnsql_create_table_v0(char* table_name,mnmetadata_list* fields);
char* mnsql_create_table_v1(mnmeta_super* tbl);
char* mnsql_sql_fields(mncstringList* field_names);
char *mnsql_sql_binding_params(mncstringList* names);
char* mnsql_sql_insert_with_params(mncstringList* names,char* table_name);
char* mnsql_sql_update_with_params(mncstringList* names,char* table_name,char* where_close);
char* mnsql_sql_delete(char* table_name,char* where_close);
mnsql* mnsql_limit_offset(mnsql* sql,size_t limit,size_t offset);
mnsql* mnsql_orderby(mnsql* sql,mnmetadata meta , db_order_dir dir);


