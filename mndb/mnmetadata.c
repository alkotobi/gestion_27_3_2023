//
// Created by merhab on 2023/3/18.
//
#include "mnmetadata.h"

mnmetadata *mnmetadata_new() {
    mnmetadata* cst=(mnmetadata*) mnalloc(sizeof(mnmetadata));
    assert(cst);
    cst->default_val = 0;
    cst->is_primary_key = 0;
    cst->is_unique = 0;
    cst->must_not_nul = 0;
    cst->is_autoinc = 0;
    cst->type=-1;
    cst->is_generated =1;
    cst->caption=0;
    return cst;
}


mnmetadata* mnmetadata_init(mnmetadata *cst,
                           char* name,
                           mntypes type,
                           int must_not_nul,
                           int is_unique,
                           int is_primary_key,
                           int is_autoinc,
                           mnvariant *default_val)
{
    if (! cst){
        cst = mnmetadata_new();
    }
    cst->name = cstring_new_clone(name);
    cst->must_not_nul = must_not_nul;
    cst->is_unique = is_unique;
    cst->is_primary_key = is_primary_key;
    cst->default_val = (default_val);
    cst->is_autoinc =is_autoinc;
    cst->type =type;
    return cst;
}

mnmetadata *mnmetadata_clean(mnmetadata *cst) {
    cstring_free_v0(cst->name);
    mnvariant_clean_free(&cst->default_val);
    return cst;
}

void mnmetadata_free(mnmetadata **cst_hld) {
    mnfree(*cst_hld);
    *cst_hld =0;
}

void mnmetadata_clean_free(mnmetadata **cst_hld) {
    mnmetadata_clean(*cst_hld);
    mnmetadata_free(cst_hld);
}

mnmetadata* mnmetadata_list_add(mnmetadata_list *arr, mnmetadata *fld_meta) {
    return (mnmetadata*) mnarray_add(arr, (void*) fld_meta);
}

mnmetadata* mnmetadata_list_set_item_at(mnmetadata_list *arr, mnmetadata *fld_meta,size_t ind) {
    if (!arr->array[ind]) arr->count++;
    arr->array[ind]=fld_meta;
    return fld_meta;
}

mnmetadata* mnmetadata_list_set_item_at_clean_ex(mnmetadata_list *arr, mnmetadata *fld_meta,size_t ind) {
    if(mnmetadata_list_item_at(arr,ind)) mnmetadata_clean_free((mnmetadata **) &arr->array[ind]);
    else arr->count++;
    arr->array[ind]=fld_meta;
    return fld_meta;
}
mnmetadata *mnmetadata_list_item_at(mnmetadata_list *arr, size_t index) {
    return (mnmetadata*) mnarray_item_at(arr, index);
}

void mnmetadata_list_clean_free(void **arr_hld) {
    mnarray_clean((mnarray*)(*arr_hld), (void (*)(void **)) mnmetadata_clean_free);
    mnarray_free((mnarray **) arr_hld);
}

mnmetadata_list *mnmetadata_list_init(mnmetadata_list *arr) {
    return mnarray_init(arr);
}

mnmetadata *mnmetadata_clone(mnmetadata *meta) {
    return mnmetadata_init(0,
                           str_cpy(meta->name),
                           meta->type,
                           meta->must_not_nul,
                           meta->is_unique,
                           meta->is_primary_key,
                           meta->is_autoinc,
                           mnvariant_clone_v0(meta->default_val));
}

mnmetadata_list *mnmetadata_list_clone(mnmetadata_list *list) {
    mnmetadata_list* l = mnmetadata_list_init(0);
    for (size_t i = 0; i <list->count ; ++i) {
        mnmetadata_list_add(l, mnmetadata_clone(mnmetadata_list_item_at(list,i)));
    }
    return l;
}

mncstringList *mnmetadata_list_fld_names_list(mnmetadata_list *list, char generated_only, char is_by_clone_names) {
    mncstringList *names = mncstringList_init(0);
    size_t count = mnarray_count(list);
    for (size_t i = 0; i < count; i++) {
        mnmetadata *meta = mnmetadata_list_item_at(list, i);
        if (generated_only) {
            if (meta->is_generated) {
                if (is_by_clone_names)
                mncstringList_add(names, str_cpy(meta->name));
                else mncstringList_add(names, meta->name);
            }
        } else {
            if (is_by_clone_names)
            mncstringList_add(names, str_cpy(meta->name));
            else mncstringList_add(names, meta->name);
        }
        }
        return names;
    }


char mnmetadata_list_generated_count(mnmetadata_list* list){
    mncstringList * names = mncstringList_init(0);
    size_t count = mnarray_count(list);
    char gen_count=0;
    for (size_t i = 0; i < count ; i++) {
        mnmetadata* meta = mnmetadata_list_item_at(list, i);
        if (meta->is_generated)
            gen_count++;
    }
    return gen_count;
}
mncstringList *mnmetadata_list_fld_names_list_generated(mnmetadata_list *list) {
    mncstringList * names = mncstringList_init(0);
    size_t count = mnarray_count(list);
    for (size_t i = 0; i < count ; i++) {
        mnmetadata* meta = mnmetadata_list_item_at(list, i);
         if (meta->is_generated)
        mncstringList_add(names,cstring_new_clone(meta->name));
    }
    return names;
}

mnmetadata_list *mnmetadata_list_clean(mnmetadata_list *arr) {
    return mnarray_clean(arr, (mnfree_fnc) mnmetadata_clean_free);
}

//todo: check all return -1


