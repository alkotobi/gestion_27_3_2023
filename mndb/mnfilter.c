//
// Created by merhab on 2023/3/24.
//
#include "mnfilter.h"

mnfilter *mnfilter_new() {
    mnfilter* flt = (mnfilter*) mnalloc(sizeof(mnfilter));
    assert(flt);
    flt->fld_name=0;
    flt->comp_op =-1;
    flt->filter_prv =0;
    flt->log_op =-1;
    flt->val = 0;
    return flt;
}

mnfilter *
mnfilter_init(mnfilter *flt, enum mnlogic_op logic_op, char *fld_name, enum mncomp_op comp_op, mnvariant *val) {
    if (!flt) flt = mnfilter_new();
    flt->log_op = logic_op;
    flt->comp_op = comp_op;
    flt->fld_name = fld_name;
    flt->val = val;
    return flt;
}

char *mnfilter_create_with_params(mnfilter *flt) {
    TRASH;
    char* str = "";
    if (flt->filter_prv) {
        str = $(cstring_new_concat_2(str, mnfilter_create_with_params(flt->filter_prv)));
        char* op ="";
        switch (flt->log_op) {

            case AND:
                op = " and ";
                break;
            case OR:
                op = " or ";
                break;
            case AND_NOT:
                op = " and not ";
                break;
            case OR_NOT:
                op = " or not ";
                break;
            default:
                mnassert(0);
        }
        str = $(cstring_new_concat_2(str,op));
    }
    char* comp ="";
    switch (flt->comp_op) {

        case EQ:
            comp = " = ";
            break;
        case GREAT:
            comp = " > ";
            break;
        case LESS:
            comp = " < ";
            break;
        case GR_OR_EQ:
            comp = " >= ";
            break;
        case LES_OR_EQ:
            comp = " <= ";
            break;
        case LIKE:
            comp = " like ";
            break;
    }
    str =cstring_new_from_concat(5,str,flt->fld_name,comp,":",flt->fld_name," ");

    EMPTY_TRASH;
    if (cstring_is_equal(str,"")) str = str_cpy("");
    return str;
}

void mnfilter_clean_free(mnfilter **flt_hld) {
    mnfilter_clean(*flt_hld);
    mnfilter_free(flt_hld);
}

mnfilter *mnfilter_clean(mnfilter *flt) {
    if (flt->filter_prv){
        mnfilter_clean_free(&flt->filter_prv);
    }
    cstring_free((void **) &flt->fld_name);
    mnvariant_clean_free(&flt->val);
    return flt;
}

void mnfilter_free(mnfilter **flt_hld){
        mnfree(*flt_hld);
        *flt_hld = 0;
    }

mnvariantList *mnfilter_vals(mnfilter *flt) {
    mnvariantList* list = mnvariantList_init(0);
    if (flt->filter_prv) {
        mnvariantList *list2 = mnfilter_vals(flt->filter_prv);
        mnarray_add_array(list2, list);
        mnvariantList_free(&list);
        list = list2;
    }
    mnvariantList *list2= mnarray_init(0);
    mnarray_add(list2,flt->val);
    mnarray_add_array(list,list2);
    mnvariantList_free(&list2);
    return list;
}

mnfilter *mnfilter_add_filter(mnfilter **filter_hld, mnfilter *sub_filter) {
    mnassert(sub_filter);
    mnassert(*filter_hld);
    sub_filter->filter_prv=*filter_hld;
    *filter_hld = sub_filter;
    return sub_filter;
}


