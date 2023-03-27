//
// Created by merhab on 2023/3/24.
//

#pragma once
#include "mnmetadata.h"
#include "mnvariantList.h"

typedef struct mnfilter mnfilter;
struct mnfilter {
    mnfilter* filter_prv;
    enum mnlogic_op log_op;
    char* fld_name;
    enum mncomp_op comp_op;
    mnvariant* val;
};
mnfilter* mnfilter_new();//tested
mnfilter *mnfilter_init(mnfilter *flt,
                        enum mnlogic_op logic_op,
                                char *fld_name,
                                enum mncomp_op comp_op,
                                        mnvariant *val);//tested
char* mnfilter_create_with_params(mnfilter* flt);//tested
mnfilter* mnfilter_clean(mnfilter* flt);//tested
void mnfilter_free(mnfilter** flt_hld) ;//tested

void mnfilter_clean_free(mnfilter** flt_hld);//tested
mnvariantList* mnfilter_vals(mnfilter* flt);//tested
mnfilter * mnfilter_add_filter(mnfilter **filter_hld, mnfilter* sub_filter);//tested
