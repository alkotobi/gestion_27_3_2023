//
// Created by merhab on 2023/3/19.
//
#include "mndictionary_t.h"
char mndictionary_test(){
    print_blue("testing mndictionary...\n");
    mndictionary* dic = mndictionary_init(0);
    print_green("creating mndictionary is ok ...\n");
    mnentry* entry = mnentry_init(0, str_cpy("user"),
                                  mnvariant_init_cstring(0, str_cpy("hello")));
    print_green("creating mnentry is ok ...\n");
    mndictionary_add(dic,&entry);
    print_green("add entry to dictionary is ok ...\n");
    entry = mnentry_init(0, str_cpy("age"), mnvariant_init_int(0,40));
    mndictionary_add(dic,&entry);
    entry = mnentry_init(0, str_cpy("age"), mnvariant_init_int(0,60));
    mndictionary_add(dic,&entry);
    print_green("add item with existing key is ok ...\n");
    for (int i = 0; i <10 ; ++i) {
        entry = mnentry_init(0, cstring_concat_multi("key_%d", i), mnvariant_init_int(0, i));
        mndictionary_add(dic,&entry);
    }
    print_green("resizing is ok ...\n");
    entry=mndictionary_item_with_key(dic,"age");
    mnentry_printf(entry);
    print_green("get entry by key is ok ...\n");
    mndictionary_printf_keys(dic);
    mndictionary_printf_vals(dic);
    mndictionary_printf_entries(dic);
    print_green("making lists:keys,vals,entries is ok ...\n");
    print_green("all working...\n");
    return 1;
}