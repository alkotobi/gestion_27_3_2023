//
// Created by merhab on {today}.
//
#pragma once



#include "mnrecord_super.h"


mnrecord_super* mnrecord_super_new(){
     mnrecord_super *record_super=(mnrecord_super*) mnalloc(sizeof(mnrecord_super));
     mnassert(record_super);
     return record_super;
}

mnrecord_super* mnrecord_super_init(mnrecord_super* record_super){
    mnvariantList_init(&record_super->var_list);
    return record_super;
}
mnrecord_super* mnrecord_super_clean(mnrecord_super* record_super){
     mnvariantList_clean(&record_super->var_list);
    return  record_super;
}
void mnrecord_super_free(mnrecord_super** record_super_hld){
     mnfree(*record_super_hld);
     *record_super_hld=0;
}
void mnrecord_super_clean_free(mnrecord_super** record_super_hld){
     mnrecord_super_clean(*record_super_hld);
     mnrecord_super_free(record_super_hld);
}

mnvariantList *mnrecord_super_new_list_dirty_indexes(mnrecord_super *record_super) {
    mnvariantList * list =mnvariantList_init(0);
    for (size_t i = 0; i <record_super->var_list.count ; ++i) {
        mnvariant* var = mnarray_mnvaraiant_at(&record_super->var_list,i);
        if (var->is_dirty){
            mnvariantList_add(list, VAR_I(i));
        }
    }
    return list;
}

mnvariantList *mnrecord_super_new_list_dirty_values(mnrecord_super *record_super, char is_by_clone_vals) {
    mnvariantList * list =mnvariantList_init(0);
    for (size_t i = 0; i <record_super->var_list.count ; ++i) {
        mnvariant* var = mnarray_mnvaraiant_at(&record_super->var_list,i);
        if (var->is_dirty){
            if (is_by_clone_vals)
            mnvariantList_add(list, mnvariant_clone_v0(var));
            else mnvariantList_add(list, var);
        }
    }
    return list;
}

void mnrecord_super_set_dirty_items_in_indexes(mnrecord_super *record_super,
                                               mnvariantList *indexes, char is_dirty) {
    for (size_t i = 0; i <indexes->count ; ++i) {
        mnvariantList_item_at(&record_super->var_list,i)->is_dirty=is_dirty;
    }
}
