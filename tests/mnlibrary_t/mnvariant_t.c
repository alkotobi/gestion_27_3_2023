#include "mnvariant_t.h"


char mnvariant_test()
{
    print_cyan("testing mnvariant\n");
    print_blue("testing printing variant\n");
    mnvariant* var = mnvariant_init_int(mnvariant_new(),5);
    char* str=mnvariant_to_new_cstring_printable(var);
    print_yellow(str);
    mnvariant_clean_free(&var);
    var = mnvariant_init_cstring(mnvariant_new(),cstring_new_clone("hello"));
    str=mnvariant_to_new_cstring_printable(var);
    print_yellow(str);
    mnvariant_clean_free(&var);
    var = mnvariant_init_double(mnvariant_new(),123.676);
    str=mnvariant_to_new_cstring_printable(var);
    print_yellow(str);
    printf("\n");
    mnvariant_clean_free(&var);
    var = mnvariant_init_int(mnvariant_new(),123);
    str=mnvariant_to_new_cstring(var);
    print_yellow(str);
    mnvariant_clean_free(&var);
    var = mnvariant_init_cstring(mnvariant_new(),cstring_new_clone("memo tab colo bara tipo"));
    str=mnvariant_to_new_cstring(var);
    print_yellow(str);
    mnvariant_clean_free(&var);
    var = mnvariant_init_double(mnvariant_new(),12.6);
    str=mnvariant_to_new_cstring(var);
    print_yellow(str);
    printf("\n");
    mnvariant_clean_free(&var);
    var = mnvariant_init_int(mnvariant_new(),123);
    str=mnvariant_to_new_cstring_out_size(var,30);
    print_yellow(str);
    mnvariant_clean_free(&var);
    var = mnvariant_init_cstring(mnvariant_new(),cstring_new_clone("memo tab colo bara tipo"));
    str=mnvariant_to_new_cstring_out_size(var,30);
    print_yellow(str);
    mnvariant_clean_free(&var);
    var = mnvariant_init_double(mnvariant_new(),12.6);
    str=mnvariant_to_new_cstring_out_size(var,30);
    print_yellow(str);
    mnvariant_clean_free(&var);
    printf("\n");
    return 1;
}
