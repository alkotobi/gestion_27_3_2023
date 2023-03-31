//
// Created by merhab on {today}.
//
#pragma once



#include "mnsystem.h"
#include "mnmetadata.h"

typedef struct {
    mnmetadata_list* meta_list;
    char* table_name;
}mnmeta_super;

mnmeta_super* mnmeta_super_new();
mnmeta_super *mnmeta_super_init(mnmeta_super *meta_super, mnmetadata_list *meta_list, char *table_name);
mnmeta_super* mnmeta_super_clean(mnmeta_super* meta_super);
void mnmeta_super_free(mnmeta_super** meta_super_hld);
void mnmeta_super_clean_free(mnmeta_super** meta_super_hld);
int64_t mnmeta_super_autoinc_index(mnmeta_super* meta_super);
char *mnmeta_super_get_primary_key_filed_name(mnmeta_super *meta_super, char is_by_copy_name);
mncstringList *
mnmeta_super_get_fields_names_list(mnmeta_super *meta_super, char only_generated, char is_by_clone_names);
mncstringList *
mnmeta_super_get_fields_names_list_by_indexes(mnmeta_super *meta_super,
                                              char only_generated,mnvariantList* list_indexes ,
                                              char is_by_clone_names);
int64_t mnmeta_super_get_autoinc_field_ind(mnmeta_super * meta_super);
int64_t mnmeta_super_get_primary_key_field_ind(mnmeta_super* meta_super);