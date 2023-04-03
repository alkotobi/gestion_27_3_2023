#include "mnvariantList.h"

mnvariantList* mnvariantList_new()
{
    return mnarray_new();
}

mnvariantList* mnvariantList_init(mnvariantList* var_list)
{
    return mnarray_init(var_list);
}

mnvariant* mnvariantList_set_item_at_clean_ex(mnvariantList* var_list,mnvariant* var,size_t ind){
    if (mnvariantList_item_at(var_list,ind)) mnvariant_clean_free((mnvariant **) &(var_list->array[ind]));
    else var_list->count++;
    var_list->array[ind] = var;
    return var;
}
mnvariant* mnvariantList_set_item_at(mnvariantList* var_list,mnvariant* var,size_t ind){
    if (!var_list->array[ind]) var_list->count++;
    var_list->array[ind] = var;
    return var;
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
        mnvariant* var = mnvariantList_item_at(list,i);
        mnvariant_printf(var);
    }

}

void mnvariantList_clean_free(mnvariantList **list_hld) {
    mnvariantList_clean(*list_hld);
    mnvariantList_free(list_hld);
}

mnvariantList *mnvariantList_new_list_dirty_indexes(mnvariantList *var_list) {
    mnvariantList * list = mnvariantList_init(0);
    for (size_t i = 0; i <var_list->count ; ++i) {
        if (mnvariantList_item_at(var_list,i)->is_dirty) mnvariantList_add(list, VAR_I(i));
    }
    return list;
}
mnvariantList* mnvariantList_new_list_dirty_values(mnvariantList* vars, char is_cloned){
    mnvariantList * list = mnvariantList_init(0);
    for (size_t i = 0; i <vars->count ; ++i) {
        mnvariant * var = mnvariantList_item_at(vars,i);
        if (var->is_dirty) {
            if (is_cloned)
                mnvariantList_add(list, mnvariant_clone_v0(var));
            else
                mnvariantList_add(list, var);
        }
    }
    return list;
}

void
mnvariantList_set_dirty_items_in_indexes(mnvariantList *var_list, mnvariantList *list_dirty_indexes, char will_dirty) {
    for (size_t i = 0; i <list_dirty_indexes->count ; ++i) {
        int index = mnvariant_int(mnvariantList_item_at(list_dirty_indexes,i));
        mnvariantList_item_at(var_list,index)->is_dirty=will_dirty;
    }
}

void mnvariantList_set_all_dirty(mnvariantList *var_list, char will_dirty){
    for (size_t i = 0; i <var_list->count ; ++i) {
        mnvariantList_item_at(var_list,i)->is_dirty =will_dirty;
    }
}