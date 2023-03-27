#include "mncstringList_t.h"

char mncstingList_test()
{
    char ret=1;
    print_cyan("testing mnstringList\n");
    print_blue("testing mncstringList_init\nmncstringList_new\nmncstringList_add_clone\nmncstringList_item_at\nmncstringList_char_count\n");
    mncstringList* list=mncstringList_init(mncstringList_new());
    mncstringList_add_clone(list,"I");
    mncstringList_add_clone(list," am");
    mncstringList_add_clone(list," nour");
    ret=ret*cstring_is_equal(mncstringList_item_at(list,0),"I");
    ret=ret*cstring_is_equal(mncstringList_item_at(list,1)," am");
    ret=ret*cstring_is_equal(mncstringList_item_at(list,2)," nour");
    ret=ret* (mncstringList_char_count(list)==9);
    test_v1(ret);
    print_blue("testing mncstringList_concat\n");    
    char* str= mncstringList_concat(list,"\n");
    ret=ret*cstring_is_equal(str,"I\n am\n nour\n");
    cstring_free((void**)&str);
    test_v1(ret);
    print_blue("testing cstring_concat_multi\n");
    char* s= cstring_concat_multi("hello %s , I am %s , my age is %d , my salary is %f",
                                  "Sofia", "Nour", 43, 12.7);
    ret =ret*cstring_is_equal(s,"hello Sofia , I am Nour , my age is 43 , my salary is 12.700000");
    cstring_free((void**)&s);
    test_v1(ret);
    mncstringList_clean_free(&list);
    mncstringList* l = mncstringList_init(0);
    for (int i = 0; i <10000 ; ++i) {
        mncstringList_add(l, str_cpy("سبحان الله "));
    }
    mncstringList_printf(l);
    mncstringList_clean_free(&l);
    return 1;
}
