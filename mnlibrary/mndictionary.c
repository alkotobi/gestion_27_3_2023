//
// Created by merhab on 2023/3/19.
//
#include "mndictionary.h"

size_t hash(const char *str,size_t size)
{
    size_t hash = 5381;
    char c;
    for (size_t i=0;str[i]!=0 ;i++ ) {
        c=str[i];
        hash = ((hash << 5) + hash) + c;
    }
    //    while (c = *str++)
    //        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if (hash<0) hash=-hash;
    return hash % size;
}

mnentry* mnentry_new(){
    mnentry * entry = (mnentry *) mnalloc(sizeof (mnentry));
    assert(entry);
    entry->val=0;
    entry->val=0;
    return entry;
}

mndictionary* mndictionary_new(){
    return mnarray_new();
}

mndictionary *mndictionary_init(mndictionary *dic) {
    return mndictionary_init_with_size(dic,ARRAY_MIN_SIZE);
}

mnentry *mnentry_init(mnentry *entry, char *key, mnvariant *var) {
    if (!entry) entry = mnentry_new();
    entry->key=key;
    entry->val = var;
    return entry;
}

mnentry *mnentry_clean(mnentry *entry) {
    cstring_free((void**)(&(entry->key)));
    mnvariant_clean_free(&(entry->val));
    return entry;
}

void mnentry_free(mnentry **entry_hld) {
    mnfree(*entry_hld);
   *entry_hld = 0;
}

void mnentry_clean_free(mnentry **entry_hld) {
    mnentry_clean(*entry_hld);
    mnentry_free(entry_hld);
}

mnentry *mndictionary_add(mndictionary *dic, mnentry **entry_hld) {
    assert(*entry_hld);
    mnentry * entry = *entry_hld;
    if (dic->count) {
        long double factor = (dic->size / (long double) dic->count);
        if (factor < 0.75) {
            dic = mndictionary_resize(dic);
        }
    }
    size_t index = hash(entry->key, dic->size);
    if (!dic->array[index]) dic->array[index]= mnarray_init(0);
    mnarray* arr = dic->array[index];
    for (size_t i = 0; i <arr->count ; ++i) {
        mnentry* ent = mnarray_item_at(arr,i);
        if (cstring_is_equal(entry->key, ent->key)){
            mnentry_clean(ent);
            ent->val=entry->val;
            ent->key = entry->key;
            mnentry_free(entry_hld);
            return ent;
        }
    }
    mnarray_add(arr, (void *) (entry));
    dic->count++;
    return entry;
}

mndictionary *mndictionary_resize(mndictionary *dic) {
    mndictionary* dic2 = mndictionary_init_with_size(0,dic->size*2);
    for (size_t i = 0; i<dic->size ; ++i) {
        if (dic->array[i]){
            mnarray* arr = dic->array[i];
            for (size_t j = 0; j <arr->count ; ++j) {
                mnentry * entry = ((mnentry*) mnarray_item_at(arr,j));
                mndictionary_add(dic2, &entry);
            }
        }
    }
    for (size_t i = 0; i <dic->size ; ++i) {
        mnfree(dic->array[i]);
    }
    mnfree(dic->array);//only free don't destroy the data
    dic->array=dic2->array;
    dic->size=dic2->size;
    dic->count=dic2->count;
    dic->index = dic2->index;
    mnfree(dic2);
    return dic;
}

void mndictionary_clean_free(mndictionary **ptr) {
    mndictionary_clean(*ptr);
    mndictionary_free(ptr);
}

mndictionary *mndictionary_init_with_size(mndictionary *dic,size_t size) {
    if (!dic) dic=mndictionary_new();
    mnarray_init_v0(dic,size);
    for (size_t i = 0; i <dic->size ; ++i) {
        dic->array[i]=0;
    }
    return dic;
}

mndictionary *mndictionary_clean(mndictionary *dic) {
    for (size_t i = 0; i <dic->size ; ++i) {
        if (dic->array[i]){
            mnarray* arr = dic->array[i];
            mnarray_clean(arr,(void (*)(void **)) mnentry_clean_free);
        }
    }
    return dic;
}

void mndictionary_free(mndictionary **dic_hld) {
    for (size_t i = 0; i < (*dic_hld)->size; ++i) {
        mnarray * arr = (mnarray*)(((*dic_hld)->array))[i];
        mnfree(arr);
        arr =0;
    }
    mnfree((*dic_hld)->array);
    mnfree(*dic_hld);
    *dic_hld =0;
}

mnentry *mndictionary_item_with_key(mndictionary *dic, char *key) {
    size_t ind = hash(key,dic->size);
    mnarray* arr = dic->array[ind];
    for (size_t i = 0; i <arr->count ; i++) {
        mnentry* entry = mnarray_item_at(arr,i);
        if (cstring_is_equal(entry->key,key)){
            return entry;
        }
    }
    assert(0);
}

mncstringList *mndictionary_key_list(mndictionary *dic) {
    mncstringList* list = mncstringList_init(0);
    for (size_t i = 0; i < dic->size ; ++i) {
        if (dic->array[i]) {
            mnarray *arr = dic->array[i];
            for (size_t j = 0; j <arr->count ; ++j) {
                mnentry* entry = mnarray_item_at(arr,j);
                mncstringList_add(list,str_cpy(entry->key));
            }
        }
    }
    return list;
}

mnvariantList *mndictionary_val_list(mndictionary *dic) {
    mnvariantList * list = mncstringList_init(0);
    for (size_t i = 0; i < dic->size ; ++i) {
        if (dic->array[i]) {
            mnarray *arr = dic->array[i];
            for (size_t j = 0; j <arr->count ; ++j) {
                mnentry* entry = mnarray_item_at(arr,j);
                mnvariantList_add(list, mnvariant_clone_v0(entry->val));
            }
        }
    }
    return list;
}

mnentry *mnentriesList_add(mnentriesList *list, mnentry *entry) {
    mnarray_add(list,entry);
    return entry;
}

mnentry *mnentriesList_item_at(mnentriesList *list, size_t ind) {
    return mnarray_item_at(list,ind);
}

mnentriesList *mnentriesList_init(mnentriesList *list) {
    return mnarray_init(list);
}

mnentriesList *mndictionary_entries_list(mndictionary *dic) {
    mnentriesList * list = mnentriesList_init(0);
    for (size_t i = 0; i < dic->size ; ++i) {
        if (dic->array[i]) {
            mnarray *arr = dic->array[i];
            for (size_t j = 0; j <arr->count ; ++j) {
                mnentry* entry = mnarray_item_at(arr,j);
                mnentriesList_add(list,entry);
            }
        }
    }
    return list;
}

void mndictionary_printf_keys(mndictionary *dic) {
    mncstringList * list = mndictionary_key_list(dic);
    for (size_t i = 0; i < list->count ; ++i) {
        printf("%s \n", mncstringList_item_at(list,i));
    }
    mncstringList_clean_free(&list);
}
void mndictionary_printf_vals(mndictionary *dic) {
    mnvariantList * list = mndictionary_val_list(dic);
    mnvariantList_printf(list);
    mnvariantList_clean(list);
    mnvariantList_free_v1(list);
}

void mndictionary_printf_entries(mndictionary *dic) {
    mnentriesList * list = mndictionary_entries_list(dic);
    for (size_t i = 0; i < list->count ; ++i) {
        printf("key:%s ", mnentriesList_item_at(list,i)->key);
        printf(" --> val=");
        mnvariant_printf(mnentriesList_item_at(list,i)->val);
    }
    mnentriesList_clean_fee(&list);
}

void mnentriesList_clean_fee(mnentriesList **list_hld) {
    mnarray_clean_free(list_hld,(void (*)(void **))mnentry_clean_free);
}

void mnentry_printf(mnentry *entry) {
    printf("key:%s ", entry->key);
    printf(" --> val=");
    mnvariant_printf(entry->val);
}



