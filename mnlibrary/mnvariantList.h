#pragma once
#include "mnvariant.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef mnarray mnvariantList;

mnvariantList* mnvariantList_new();
mnvariantList* mnvariantList_init(mnvariantList* var_list);
mnvariant* mnvariantList_add(mnvariantList* var_list,mnvariant* var);
mnvariantList* mnvariantList_clean(mnvariantList* var_list);
void mnvariantList_free(mnvariantList** var_list_hld);
void mnvariantList_free_v1(mnvariantList* var_list);
mnvariant* mnvariantList_item_at(mnvariantList* var_list,size_t ind);
void mnvariantList_printf(mnvariantList* list);
void mnvariantList_clean_free(mnvariantList** list_hld);

#ifdef __cplusplus
}
#endif