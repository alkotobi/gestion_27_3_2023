#include "cstring_test.h"


char cstring_test()
{
    char ret=1;
    print_cyan("testing cstring\n");
    print_blue("testing cstring_new,cstring_free,cstring_is_empty....\n");
    char* str=cstring_new();
    ret=ret*cstring_is_empty(str);
    cstring_free((void**)&str);
    test_v1(ret);
    print_blue("testing cstring_new_fill_with_char....\n"
    "cstring_count...\n"
    "cstring_is_equal...\n");
    str=cstring_new_fill_with_char('a',3);
    ret=ret*(cstring_count(str)==3);
    ret=ret*(cstring_is_equal(str,"aaa"));
    test_v1(ret);
    print_blue("testing cstring_new_clone...\n");
    char* str2 = cstring_new_clone(str);
    ret=ret*(str2!=str);
    ret=ret*cstring_is_equal(str,str2);
    cstring_free((mnptrhld)&str2);
    test_v1(ret);
    print_blue("testing cstring_new_copy_with_char_count...\n");
    str2=cstring_new_copy_with_char_count(str,1);
     ret=ret*(str2!=str);
    ret=ret*cstring_is_equal("a",str2);
    cstring_free((mnptrhld)&str2);
    test_v1(ret);   
    print_blue("testing cstring_new_from_concat...\n");
    str2=cstring_new_from_concat(3,"I"," am"," nour");
    ret=ret*cstring_is_equal(str2,"I am nour");
    cstring_free((mnptrhld)&str2);
    test_v1(ret);
    print_blue("testing cstring_new_from_concat_v1...\ncstring_new_from_concat_with_nl...\n"); 
    mnarray* arr =mnarray_init(mnarray_new());
    mnarray_add(arr,"I");
    mnarray_add(arr," am");
    mnarray_add(arr," nour");
    str2=cstring_new_from_concat_v1((char**)(arr->array),arr->count);
    ret=ret*cstring_is_equal(str2,"I am nour");
    cstring_free((mnptrhld)&str2);
    str2=cstring_new_from_concat_with_nl((char**)(arr->array),arr->count);
    ret=ret*cstring_is_equal(str2,"I\n am\n nour\n");
    mnarray_free(&arr);
    test_v1(ret); 
    print_blue("testing cstring_is_greater...\n"); 
    ret=ret*(cstring_is_greater("ba","ab"));
    test_v1(ret);   
    print_blue("testing cstring_add...\n"); 
    cstring_add(&str,"a");
    ret=ret*cstring_is_equal(str,"aaaa");
    test_v1(ret);
    print_blue("testing cstring_replace_sub_string_at...\n"); 
    cstring_replace_sub_string_at(str,1,"bbbbbbb");
    ret=ret*cstring_is_equal(str,"abbb");
    test_v1(ret);
    cstring_free((void**)&str);
    return ret;
}

