//
// Created by merhab on 2023/3/26.
//

#include "mnfilter_t.h"

char mnfilter_t() {
    mnfilter* filter = mnfilter_new();
    mnfilter_init(filter, AND,
                  str_cpy("name"), EQ,
                  mnvariant_init_cstring_cpy(0, "nour"));
    char*str=mnfilter_create_with_params(filter);

    mnfilter_add_filter(&filter, mnfilter_init(0, AND,
                                               str_cpy("age"),
                                               EQ, mnvariant_init_int(0,25)));
    mnfilter_add_filter(&filter, mnfilter_init(0, OR,
                                               str_cpy("salary"),
                                               EQ, mnvariant_init_double(0,200.25)));
    cstring_free((void **) &str);
    str = mnfilter_create_with_params(filter);
    printf("%s\n",str);
    mnvariantList* l=mnfilter_vals(filter);
    mnvariantList_printf(l);
    char res =  cstring_is_equal(str,"name = :name and age = :age or salary = :salary");
    test(res,"testing mnfilter_new mnfilter_init mnfilter_create_with_params...\n");
    printf("\n");
    mnfilter_clean(filter);
    res = res * (filter->filter_prv==0 && filter->val==0 && filter->fld_name ==0);
    test(res,"filter cleaning test.....\n");
    mnfilter_free(&filter);
    res=res*(filter==0);
    test(res,"freeing filter testing...\n");
    return 0;
}
