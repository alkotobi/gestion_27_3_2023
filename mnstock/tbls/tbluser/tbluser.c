//
// Created by merhab on 2023/3/25.
//
#include "tbluser.h"

tbluser_meta *tbluser_meta_new() {
    tbluser_meta* user = (tbluser_meta*) mnalloc(sizeof(tbluser_meta));
    mnassert(user);
    user->id_group=0;
    user->id=0;
    user->pass =0;
    user->title =0;
    user->usr =0;
    user->super.meta_list=0;
    return user;
}

tbluser_meta *tbluser_meta_init(tbluser_meta *user) {
    if (!user) user = tbluser_meta_new();
    user->super.meta_list=mnmetadata_list_init(0);
    user->super.table_name ="usr";
    user->usr= mnmetadata_list_add(user->super.meta_list,
                                   mnmetadata_init(0, str_cpy("user"),
                                                   CString,1,1,
                                                   0,0,0));
    user->title= mnmetadata_list_add(user->super.meta_list,
                                     mnmetadata_init(0, str_cpy("title"),
                                                     CString,1,0,
                                                     0,0,0));
    user->pass= mnmetadata_list_add(user->super.meta_list,
                                    mnmetadata_init(0, str_cpy("pass"),
                                                    CString,1,0,
                                                    0,0,0));
    user->id= mnmetadata_list_add(user->super.meta_list,
                                  mnmetadata_init(0, str_cpy("id"),
                                                  Big_int,1,1,1,
                                                  1,0));
    return user;
}

void tbluser_meta_free(tbluser_meta **user_hld) {
    mnarray_free(&((*user_hld)->super.meta_list));
    mnfree(*user_hld);
    *user_hld =0;
}

void tbluser_meta_clean_free(tbluser_meta **user_hld) {
    tbluser_meta_clean(*user_hld);
    tbluser_meta_free(user_hld);
}

tbluser_meta* tbluser_meta_clean(tbluser_meta* user) {
    mnmetadata_list_clean(user->super.meta_list);
    user->id=0;
    user->pass=0;
    user->title=0;
    user->id_group =0;
    user->usr=0;
    return user;
}

char *tbluser_create_table_sql(tbluser_meta* user) {
    return mnsql_create_table_v0(user->super.table_name,user->super.meta_list);
}

tbluser_record *
tbluser_record_init(tbluser_record *record, mnvariant *id, mnvariant *title,
                    mnvariant *usr, mnvariant *pass,
                    mnvariant *id_group) {
    if (!record) record=tbluser_record_new();
    mnvariantList_init(&record->var_list);
    record->id = id;
    mnvariantList_add(&record->var_list,record->id);
    record->title = title;
    mnvariantList_add(&record->var_list,record->title);
    record->usr= usr;
    mnvariantList_add(&record->var_list,record->usr);
    record->pass = pass;
    mnvariantList_add(&record->var_list,record->pass);
    record->id_group=id_group;
    mnvariantList_add(&record->var_list,record->id_group);
    return record;
}
tbluser_record* tbluser_record_refresh(tbluser_record *record) {
    mnvariantList_clean(&record->var_list);
    mnvariantList_add(&record->var_list,record->id);
    mnvariantList_add(&record->var_list,record->title);
    mnvariantList_add(&record->var_list,record->usr);
    mnvariantList_add(&record->var_list,record->pass);
    mnvariantList_add(&record->var_list,record->id_group);
    return record;
}

tbluser_record *tbluser_record_new() {
    tbluser_record* record = (tbluser_record*) mnalloc(sizeof(tbluser_record));
    mnassert(record);
    record->usr=0;
    record->id_group=0;
    record->title=0;
    record->pass=0;
    record->id=0;
    return record;
}

tbluser_record *tbluser_record_clean(tbluser_record *record) {
    mnarray_clean(&record->var_list, (mnfree_fnc) mnvariant_clean_free);
    record->usr=0;
    record->id_group=0;
    record->title=0;
    record->pass=0;
    record->id=0;
    return record;
}

void tbluser_record_free(tbluser_record **rec_hld) {
    mnfree(*rec_hld);
    *rec_hld=0;
}


