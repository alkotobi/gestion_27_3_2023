//
// Created by merhab on 2023/3/19.
//

#pragma once

#include "mnsystem.h"
#include "mnarray.h"
#include "mnvariantList.h"
#include "mncstringList.h"

size_t hash(const char *str,size_t size);
typedef mnarray mndictionary;
typedef struct {
    char * key;
    mnvariant* val;
}mnentry;
mnentry* mnentry_new();
mnentry *mnentry_init(mnentry *mnentry, char *key, mnvariant *var);
mnentry* mnentry_clean(mnentry* entry);
void mnentry_free(mnentry** entry_hld);
void mnentry_clean_free(mnentry** entry_hld);
void mnentry_printf(mnentry* entry);
mndictionary* mndictionary_new();
mndictionary* mndictionary_init(mndictionary* dic);
mndictionary* mndictionary_init_with_size(mndictionary* dic,size_t size);
mnentry *mndictionary_add(mndictionary *dic, mnentry **entry_hld);
void mndictionary_clean_free(mndictionary **ptr);
mndictionary* mndictionary_clean(mndictionary* dic);
void mndictionary_free(mndictionary** dic_hld);
mndictionary* mndictionary_resize(mndictionary* dic);
mnentry* mndictionary_item_with_key(mndictionary* dic,char* key);
mncstringList* mndictionary_key_list(mndictionary* dic);
mnvariantList* mndictionary_val_list(mndictionary* dic);
typedef mnarray mnentriesList;
mnentry* mnentriesList_add(mnentriesList* list,mnentry* entry);
mnentry* mnentriesList_item_at(mnentriesList* list, size_t ind);
mnentriesList * mnentriesList_init(mnentriesList* list);
mnentriesList* mndictionary_entries_list(mndictionary* dic);
void mnentriesList_clean_fee(mnentriesList** list_hld);
void mndictionary_printf_keys(mndictionary* dic);
void mndictionary_printf_vals(mndictionary *dic);
void mndictionary_printf_entries(mndictionary *dic);