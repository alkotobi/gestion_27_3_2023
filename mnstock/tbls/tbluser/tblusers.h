//
// Created by merhab on {today}.
//
#pragma once
#include "mnsql.h"
#include "mnmetadata.h"
#include "mnrecord_super.h"
#include "mnmeta_super.h"
#define tblusers_fields_count 5
typedef enum{Id,Title,Login,Pass,Id_group} tblusers_fields_index;
typedef struct {
    mnmeta_super super;
    mnmetadata* id;
    mnmetadata* title;
    mnmetadata* login;
    mnmetadata* pass;
    mnmetadata* id_group;
}tblusers_meta;
tblusers_meta *tblusers_meta_new();
tblusers_meta *tblusers_meta_init(tblusers_meta * meta);
tblusers_meta *tblusers_meta_clean(tblusers_meta * meta);
void tblusers_meta_free(tblusers_meta ** meta_hld);
void tblusers_meta_clean_free(tblusers_meta ** meta_hld);


typedef struct {
    //mnvariantList var_list;
mnrecord_super super;
    mnvariant* id;
    mnvariant* title;
    mnvariant* login;
    mnvariant* pass;
    mnvariant* id_group;
}tblusers_record;
tblusers_record *tblusers_record_init(tblusers_record *record,    mnvariant* id,
    mnvariant* title,
    mnvariant* login,
    mnvariant* pass,
    mnvariant* id_group);
tblusers_record *tblusers_record_clean(tblusers_record * record);
void tblusers_record_free(tblusers_record ** record_hld);
tblusers_record * tblusers_record_new();
mnvariant * tblusers_record_list_set_field_at(tblusers_record * record,mnvariant *field,tblusers_fields_index ind);
mnvariant * tblusers_record_list_set_field_at_clean_ex(void  *record_,mnvariant *field,char ind);
void  tblusers_record_set_id(tblusers_record * record,mnvariant* id,char will_make_dirty);
void  tblusers_record_set_title(tblusers_record * record,mnvariant* title,char will_make_dirty);
void  tblusers_record_set_login(tblusers_record * record,mnvariant* login,char will_make_dirty);
void  tblusers_record_set_pass(tblusers_record * record,mnvariant* pass,char will_make_dirty);
void  tblusers_record_set_id_group(tblusers_record * record,mnvariant* id_group,char will_make_dirty);
