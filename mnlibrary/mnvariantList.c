#include "mnvariantList.h"

mnvariantList* mnvariantList_new()
{
    return mnarray_new();
}

mnvariantList* mnvariantList_init(mnvariantList* var_list)
{
    return mnarray_init(var_list);
}

mnvariant* mnvariantList_add(mnvariantList* var_list,mnvariant* var)
{
    return (mnvariant*) mnarray_add(var_list,var);
}

mnvariantList* mnvariantList_clean(mnvariantList* var_list)
{
    mnarray_clean_mnvariant(var_list);
    return var_list;
}

void mnvariantList_free(mnvariantList** var_list_hld)
{
    mnarray_free(var_list_hld);
}

void mnvariantList_free_v1(mnvariantList* var_list)
{
    mnarray_free(&var_list);
}

mnvariant* mnvariantList_item_at(mnvariantList* var_list,size_t ind)
{
    return (mnvariant*) mnarray_item_at(var_list,ind);
}

void mnvariantList_printf(mnvariantList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        mnvariant_printf(mnvariantList_item_at(list,i));
    }

}

void mnvariantList_clean_free(mnvariantList **list_hld) {
    mnvariantList_clean(*list_hld);
    mnvariantList_free(list_hld);
}
