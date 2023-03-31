//
// Created by merhab on {today}.
//
#pragma once



#include "mnmeta_super.h"


mnmeta_super* mnmeta_super_new(){
     mnmeta_super *meta_super=(mnmeta_super*) mnalloc(sizeof(mnmeta_super));
     mnassert(meta_super);
     meta_super->meta_list=0;
     meta_super->table_name=0;

     //ur code here

     return meta_super;
}
mnmeta_super *mnmeta_super_init(mnmeta_super *meta_super, mnmetadata_list *meta_list, char *table_name) {
    if (!meta_super) meta_super = mnmeta_super_new();
    meta_super->meta_list=meta_list;
    meta_super->table_name=table_name;
 return meta_super;
}
mnmeta_super *mnmeta_super_init_v0(mnmeta_super *meta_super,char *table_name) {
    return mnmeta_super_init(meta_super, mnmetadata_list_init(0),table_name);
}
mnmeta_super* mnmeta_super_clean(mnmeta_super* meta_super){
    mnmetadata_list_clean_free((void **) (&meta_super->meta_list));
    cstring_free((void **) &meta_super->table_name);
 return meta_super;
}
void mnmeta_super_free(mnmeta_super** meta_super_hld){
     mnfree(*meta_super_hld);
     *meta_super_hld=0;
}
void mnmeta_super_clean_free(mnmeta_super** meta_super_hld){
     mnmeta_super_clean(*meta_super_hld);
     mnmeta_super_free(meta_super_hld);
}

int64_t mnmeta_super_autoinc_index(mnmeta_super *meta_super) {
    for (size_t i = 0; i < meta_super->meta_list->count ; ++i) {
        mnmetadata* meta = mnmetadata_list_item_at(meta_super->meta_list, i);
        if (meta->is_autoinc) return i;
    }
    return -1;
}

char *mnmeta_super_get_primary_key_filed_name(mnmeta_super *meta_super, char is_by_copy_name) {
    for (size_t i = 0; i < meta_super->meta_list->count ; ++i) {
        mnmetadata* m = mnarray_item_at(meta_super->meta_list, i);
        if (m->is_primary_key) {
            if (is_by_copy_name)
            return str_cpy(m->name);
            else return m->name;
        }
    }
    mnassert(0);
    return 0;
}

mncstringList *
mnmeta_super_get_fields_names_list(mnmeta_super *meta_super, char only_generated, char is_by_clone_names) {
    mnmetadata* meta =0;
    mncstringList * list = mncstringList_init(0);
    for (size_t i= 0; i <meta_super->meta_list->count ; ++i) {
        meta = mnarray_item_at(meta_super->meta_list,i);
        if(only_generated){
            if(meta->is_generated){
                if (is_by_clone_names)
                mncstringList_add(list, str_cpy(meta->name));
                else mncstringList_add(list, meta->name);
            }
        } else{
            if (is_by_clone_names)
            mncstringList_add(list, str_cpy(meta->name));
            else mncstringList_add(list, meta->name);
        }
    }
    return list;
}

int64_t mnmeta_super_get_autoinc_field_ind(mnmeta_super *meta_super) {
    for (size_t i= 0; i <meta_super->meta_list->count ; ++i) {
        mnmetadata* meta = mnarray_item_at(meta_super->meta_list, i);
        if (meta->is_autoinc) return i;
    }
    return -1;
}

int64_t mnmeta_super_get_primary_key_field_ind(mnmeta_super *meta_super) {
    for (size_t i= 0; i <meta_super->meta_list->count ; ++i) {
        mnmetadata* meta = mnarray_item_at(meta_super->meta_list, i);
        if (meta->is_primary_key) return i;
    }
    return -1;
}

mncstringList *mnmeta_super_get_fields_names_list_by_indexes(mnmeta_super *meta_super, char only_generated,
                                                             mnvariantList *list_indexes, char is_by_clone_names) {
   mncstringList* list = mncstringList_init(0);
    for (size_t i = 0; i <list_indexes->count ; ++i) {
        char* name=mnmetadata_list_item_at(meta_super->meta_list,
                                           mnvariant_int(mnvariantList_item_at(list_indexes,i)))->name;
        if (is_by_clone_names)
        mncstringList_add(list, str_cpy(name) );
        else mncstringList_add(list,name );
    }
    return list;
}
