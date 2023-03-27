#include "mnstring_t.h"


char mnstring_test()
{
    char res=1;
    print_cyan("testing mnstring\n");
    res=res*mnstring_isequal_t();
    res=res*mnstring_new_from_cstring_t();
    res=res*mnstring_new_from_mnstring_t();
    res=res*mnstring_new_from_concat_t();
    res=res*mnstring_from_int_t();
    res=res*mnstring_concat_multi_t();
    res=res*mnstring_concat_t();
    res=res*mnstring_concat_msstr_cstr_t();
    mnstring* str1=mnstring_init_cstring_cpy(0,"ab");
    mnstring* str2=mnstring_init_cstring_cpy(0,"ba");
    res=res*(mnstring_is_greater(str2,str1));
    print_blue("testing mnstring_is_greater...\n");
    test_v1(res);
    print_blue("testing mnstring_clone...\n");
    mnstring* str3=mnstring_clone(str1);
    res=res*mnstring_is_equal(str3,str1);
    test_v1(res);
    print_blue("testing mnstring_new_from_double...\n");
    mnstring_free_v0(str1);
    mnstring_free_v0(str2);
    mnstring_free_v0(str3);
    str1=mnstring_new_from_double(1.5);
    res=res*cstring_is_equal(str1->string,"1.500000");
    mnstring_free_v0(str1);
     test_v1(res);
    print_blue("testing mnstring_new_from_array...\n");
    mnarray* arr=mnarray_init(0);
    mnarray_add(arr,mnstring_init_cstring_cpy(0,"I"));
    mnarray_add(arr,mnstring_init_cstring_cpy(0," am"));
    mnarray_add(arr,mnstring_init_cstring_cpy(0," nour"));
    str1=mnstring_new_from_array(arr);
    res=res*cstring_is_equal(str1->string,"I am nour");
    mnstring_free_v0(str1);
    mnarray_clean_mnstring(arr);
    mnarray_free(&arr);
    test_v1(res);
    return res;
}

char mnstring_isequal_t()
{
    print_blue("char mnstring_isequal(mnstring*,mnstring*)...\n");
    mnstring* str1=mnstring_init_cstring_cpy(0,"allah is great");
    mnstring* str2 = mnstring_init_cstring_cpy(0,"allah is great");
    char res=mnstring_is_equal(str1,str2);
    test(res,"mnstring_isequal work\n");

    mnstring_free(&str1);
    mnstring_free(&str2);
    return res;
}

char mnstring_new_from_cstring_t()
{
    print_blue("mnstring* mnstring_new_from_cstring(char*)...\n");
    char* s= "allah is great";
    mnstring* str=mnstring_init_cstring_cpy(0,s);
    char res=(str->count==14);
    res=res*cstring_is_equal(str->string,s);
    test(res,"mnstring_new_from_cstring working\n");
    mnstring_free(&str);
    return res;
}

char mnstring_new_from_mnstring_t()
{
    print_blue("mnstring* mnstring_new_from_mnstring(mnstring*)...\n");
    mnstring* s=mnstring_init_cstring_cpy(0,"allah is great");
    mnstring* str=mnstring_new_from_mnstring(s);
    char res=(str->count==s->count);
    res=res*cstring_is_equal(str->string,s->string);
    res=res*mnstring_is_equal(str,s);
    test(res,"mnstring_new_from_mnstring working\n");
    mnstring_free(&s);
    mnstring_free(&str);
    return res;
}

char mnstring_new_from_concat_t()
{
    print_blue("mnstring* mnstring_new_from_concat(int* ...)...\n");
    mnstring* s=mnstring_init_cstring_cpy(0,"allah is great");
    mnstring* s2=mnstring_init_cstring_cpy(0," allah akbar");
    mnstring* str=mnstring_new_from_concat(2,s,s2);
    char res=(str->count==s->count+s2->count);
    res=res*(str->size==s->size+s2->size);
    char* cs=cstring_new_from_concat(2,s->string,s2->string);
    res=res*cstring_is_equal(str->string,cs);
    test(res,"mnstring_new_from_concat working\n");
    mnstring_free(&s);
    mnstring_free(&str);
    mnstring_free(&s2);
    free(cs);
    return res;
}

char mnstring_from_int_t()
{
    print_blue("mnstring* mnstring_from_int(int)...\n");
    mnstring* str=mnstring_new_from_int(10);
    char res=(str->count==2);
    res=res*cstring_is_equal(str->string,"10");
    mnstring_free(&str);
    test(res,"mnstring_from_int working for + \n");
    str=mnstring_new_from_int(-10);
    res=res*(str->count==3);
    res=res*cstring_is_equal(str->string,"-10");
    mnstring_free(&str);
    test(res,"mnstring_from_int working for - \n");
    return res;
}

char mnstring_concat_multi_t()
{
    print_blue("testing mnstring_concat_multi...\n");
    mnstring* s=mnstring_init_cstring_cpy(0,"ana");
    mnstring* str=mnstring_new_concat_multi("this %d is %m then %s",1,s,"lala");
    char res= cstring_is_equal(str->string,"this 1 is ana then lala");
    mnstring_free(&s);
    mnstring_free(&str);
    test(res," working\n");
    return res;
}

char mnstring_concat_t()
{
    print_blue("testing mnstring_concat...\n");
    mnstring* s=mnstring_init_cstring_cpy(0,"ana ");
    mnstring* str_sub=mnstring_init_cstring_cpy(0,"howa");
    mnstring_concat(s,str_sub);
    char res= cstring_is_equal(s->string,"ana howa");
    mnstring_free(&s);
    mnstring_free(&str_sub);
    test(res," working\n");
    return res;
}

char mnstring_concat_msstr_cstr_t()
{
    print_blue("testing mnstring_concat_msstr_cstr...\n");
    mnstring* s=mnstring_init_cstring_cpy(0,"ana ");
    mnstring_concat_msstr_cstr(s,"howa");
    char res= cstring_is_equal(s->string,"ana howa");
    mnstring_free(&s);
    test(res," working\n");
    return res;
}
