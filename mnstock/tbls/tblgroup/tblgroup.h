//
// Created by merhab on {today}.
//
#pragma once
#include "mnsql.h"
#include "mnmetadata.h"
char tblgroup_fields_count=4;
typedef enum{Id,Grp_name,Can_login,Can_edit_group} tblgroup_fields_index;
typedef struct {
    tbl_super super;
    mnmetadata* id;
    mnmetadata* grp_name;
    mnmetadata* can_login;
    mnmetadata* can_edit_group;
}tblgroup_meta;
tblgroup_meta *tblgroup_meta_new();
tblgroup_meta *tblgroup_meta_init(tblgroup_meta * grp);
tblgroup_meta *tblgroup_meta_clean(tblgroup_meta * grp);
void tblgroup_meta_free(tblgroup_meta ** grp_hld);
void tblgroup_meta_clean_free(tblgroup_meta ** grp_hld);


typedef struct {
    mnvariantList var_list;
    void(*refresh_list)(void*);
}record_super;
typedef struct {
    //mnvariantList var_list;
    record_super super;
    mnvariant* id;
    mnvariant* grp_name;
    mnvariant* can_login;
    mnvariant* can_edit_group;
}tblgroup_record;
tblgroup_record *tblgroup_record_init(tblgroup_record *record,    mnvariant* id,
                                      mnvariant* grp_name,
                                      mnvariant* can_login,
                                      mnvariant* can_edit_group);
void   tblgroup_record_refresh_list(void  *record_);
tblgroup_record *tblgroup_record_clean(tblgroup_record * record);
void tblgroup_record_free(tblgroup_record ** record_hld);
tblgroup_record * tblgroup_record_new();
mnvariant * tblgroup_record_list_set_field_at(tblgroup_record * record,mnvariant *field,tblgroup_fields_index ind);
mnvariant * tblgroup_record_list_set_field_at_clean_ex(tblgroup_record * record,mnvariant *field,tblgroup_fields_index ind);
void  tblgroup_record_set_id(tblgroup_record * record,mnvariant* id);
void  tblgroup_record_set_grp_name(tblgroup_record * record,mnvariant* grp_name);
void  tblgroup_record_set_can_login(tblgroup_record * record,mnvariant* can_login);
void  tblgroup_record_set_can_edit_group(tblgroup_record * record,mnvariant* can_edit_group);
