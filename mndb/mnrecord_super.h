//
// Created by merhab on {today}.
//
#pragma once
#include "mnsystem.h"
#include "mnvariantList.h"
typedef struct {
    mnvariantList var_list;
    mnvariant* (*var_list_set_field_at_clean_ex)(void*, mnvariant*, char);
}mnrecord_super;

mnrecord_super* mnrecord_super_new();
mnrecord_super* mnrecord_super_init(mnrecord_super* record_super);
mnrecord_super* mnrecord_super_clean(mnrecord_super* record_super);
void mnrecord_super_free(mnrecord_super** record_super_hld);
void mnrecord_super_clean_free(mnrecord_super** record_super_hld);
mnvariantList *mnrecord_super_new_list_dirty_indexes(mnrecord_super *record_super);
mnvariantList *mnrecord_super_new_list_dirty_values(mnrecord_super *record_super, char is_by_clone_vals);
void mnrecord_super_set_dirty_items_in_indexes(mnrecord_super* record_super,mnvariantList* indexes,char is_dirty);

