//
// Created by merhab on 2023/3/25.
//

#pragma once
#include "mnsql.h"
#include "mnmetadata.h"


typedef struct {
    tbl_super super;//work like inheritance
    mnmetadata* id;
    mnmetadata* title;
    mnmetadata* usr;
    mnmetadata* pass;
    mnmetadata* id_group;
}tbluser_meta;

tbluser_meta* tbluser_meta_new();//tested
tbluser_meta* tbluser_meta_init(tbluser_meta* user);//tested
tbluser_meta* tbluser_meta_clean(tbluser_meta* user);
void tbluser_meta_free(tbluser_meta **user_hld);
void tbluser_meta_clean_free(tbluser_meta **user_hld);
char* tbluser_create_table_sql(tbluser_meta* user);

typedef struct {
    mnvariantList var_list;
    mnvariant* id;
    mnvariant* title;
    mnvariant* usr;
    mnvariant* pass;
    mnvariant* id_group;
}tbluser_record;

tbluser_record * tbluser_record_init(tbluser_record *record,
                                     mnvariant *id, mnvariant *title,
                                     mnvariant *usr, mnvariant *pass,
                                     mnvariant *id_group);
tbluser_record* tbluser_record_refresh(tbluser_record* record);
tbluser_record* tbluser_record_new();
tbluser_record* tbluser_record_clean(tbluser_record* record);
void tbluser_record_free(tbluser_record** rec_hld);