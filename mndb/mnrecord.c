//
// Created by merhab on 2023/3/18.
//
#include "mnrecord.h"
mnrecordset* mnrecordset_new(){
    return mnarray_new();
}
mnrecord *mnrecordset_add(mnrecordset *rdset, mnrecord *rd) {
    return (mnrecord*) mnarray_add(rdset,rd);
}

mnrecordset *mnrecordset_clean(mnrecordset *rdset) {
    return mnarray_clean(rdset,(void (*)(void **))mnvariant_clean_free);
}

void mnrecordset_free(mnrecordset **rdset_hld) {
    mnfree(*rdset_hld);
    *rdset_hld =0;
}

void mnrecordset_clean_free(mnrecordset **rdset_hld) {
    mnrecordset_clean(* rdset_hld);
    mnrecordset_free(rdset_hld);
}

mnrecordset *mnrecordset_init(mnrecordset *rds) {
    return mnarray_init(rds);
}
