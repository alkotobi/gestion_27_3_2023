#pragma once
#include <stdio.h>
#include "mnsystem.h"
#include "mncstring.h"
#include "mnarray.h"


#ifdef __cplusplus
extern "C"
{
#endif


struct mnvariant{
    mntypes data_type;
    mnvar val;
    mnfree_fnc free_me;
};
typedef struct mnvariant mnvariant ;

mnvariant* mnvariant_init(mnvariant* var,     mntypes data_type,
              mnvar val,
              mnfree_fnc free_me);//tested
void mnvariant_clean(mnvariant * var);//tested
mnvariant* mnvariant_new();//tested
void mnvariant_free(mnvariant** var_hld);//tested
mnvar mnvariant_value(mnvariant* var);//tested
mnvar mnvariant_set_value(mnvariant* var ,mnvar value);//return old val
mntypes mnvariant_type(mnvariant* var);//tested
void mnvariant_set_type(mnvariant* var,mntypes data_type);//tested
void mnvariant_clean_free(mnvariant** var_hld);//tested
void mnvariant_clean_free_v0(mnvariant *var);
mnvariant* mnvariant_clone(mnvariant* var,mnf_var_var clone_val);//tested
mnvariant* mnvariant_init_int(mnvariant *var, int n);//tested
#define VAR_I(X) mnvariant_init_int(0,X)
int mnvariant_int(mnvariant* var);//tested
mnvariant* mnvariant_init_double(mnvariant *var, double n);//tested
#define VAR_D(X) mnvariant_init_double(0,X)
double mnvariant_double(mnvariant* var);//tested
mnvariant* mnvariant_init_cstring(mnvariant *var, char *str);//tested
#define VAR_S(X) mnvariant_init_cstring(0,str_cpy(X))
mnvariant* mnvariant_init_cstring_cpy(mnvariant *var, char *str);
mnvariant *mnvariant_init_big_int(mnvariant* var,long long int big_int);
#define VAR_BI(X) mnvariant_init_big_int(0,X)
long long int mnvariant_big_int(mnvariant* var);
char* mnvariant_cstring_ret_ref(mnvariant* var);//tested
char* mnvariant_cstring_ret_cpy(mnvariant* var);
char* mnvariant_to_new_cstring_printable(mnvariant* var);//tested
char* mnvariant_to_new_cstring_out_size(mnvariant* var,size_t out_size);//tested
char* mnvariant_to_new_cstring(mnvariant* var);//tested
mnvariant* mnarray_add_variant(mnarray* arr,mnvariant* var);
mnvariant* mnarray_mnvaraiant_at(mnarray* arr, size_t ind);
mnarray* mnarray_clean_mnvariant(mnarray* arr);
size_t mnarray_search_first_mnvariant(mnarray *arr,mnvariant *var_to_search);
size_t mnarray_search_next_mnvariant(mnarray *arr,mnvariant *var_to_search);
char mnvariant_is_equal(mnvariant *var1,mnvariant *var2);
mnvariant *mnvariant_clone_v0(mnvariant* var);
void mnvariant_printf(mnvariant* var);
#ifdef __cplusplus
}
#endif
