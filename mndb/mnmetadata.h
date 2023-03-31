//
// Created by merhab on 2023/3/18.
//

#pragma once
#include "mnsystem.h"
#include "mnvariant.h"
#include "mnarray.h"
#include "mncstringList.h"
#include "mnvariantList.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct
{
    char* name;
    mntypes type;
    int must_not_nul;// o for can null
    mnvariant * default_val;// must init/free
    int is_unique;// 0 not unique
    int is_primary_key;
    int is_autoinc;
    int is_generated;
}mnmetadata;


mnmetadata* mnmetadata_new();
mnmetadata* mnmetadata_init(mnmetadata* cst,
                           char* name,
                           mntypes type,
                           int must_not_nul,
                           int is_unique,
                           int is_primary_key,
                           int is_autoinc,
                           mnvariant * default_val
);
mnmetadata* mnmetadata_clean(mnmetadata* cst);
void mnmetadata_free(mnmetadata** cst_hld);
void mnmetadata_clean_free(mnmetadata** cst_hld);
mnmetadata* mnmetadata_clone(mnmetadata* meta);

//*****************mnfield
typedef mnvariant mnfield;
//***********************

//*********************mnmetadata_list
typedef mnarray mnmetadata_list;
mnmetadata_list* mnmetadata_list_init(mnmetadata_list* arr);//tested
mnmetadata* mnmetadata_list_add(mnmetadata_list* arr, mnmetadata* fld_meta);//tested
mnmetadata* mnmetadata_list_set_item_at(mnmetadata_list *arr, mnmetadata *fld_meta,size_t ind);
mnmetadata* mnmetadata_list_set_item_at_clean_ex(mnmetadata_list *arr, mnmetadata *fld_meta,size_t ind);
mnmetadata* mnmetadata_list_item_at(mnmetadata_list* arr, size_t index);
void mnmetadata_list_clean_free(void** arr_hld);
mnmetadata_list* mnmetadata_list_clean(mnmetadata_list* arr);
mnmetadata_list* mnmetadata_list_clone(mnmetadata_list* list);
mncstringList *mnmetadata_list_fld_names_list(mnmetadata_list *list, char generated_only, char is_by_clone_names);//tested
mncstringList *mnmetadata_list_fld_names_list_generated(mnmetadata_list *list);//tested
//*********************




#ifdef __cplusplus
}
#endif
