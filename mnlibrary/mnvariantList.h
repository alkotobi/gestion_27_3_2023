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
mnvariant* mnvariantList_set_item_at_clean_ex(mnvariantList* var_list,mnvariant* var,size_t ind);
mnvariant* mnvariantList_set_item_at(mnvariantList* var_list,mnvariant* var,size_t ind);
mnvariantList * mnvariantList_new_list_dirty_indexes(mnvariantList* var_list);
mnvariantList* mnvariantList_new_list_dirty_values(mnvariantList* vars, char is_cloned);
void mnvariantList_set_dirty_items_in_indexes(mnvariantList* var_list,mnvariantList *list_dirty_indexes,char will_dirty);
void mnvariantList_set_all_dirty(mnvariantList *var_list, char will_dirty);
#ifdef __cplusplus
}
#endif