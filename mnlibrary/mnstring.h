#ifndef MNSTRING_H
#define MNSTRING_H

#include "mnsystem.h"
#include "mncstring.h"
#include <stdio.h>
#include "mnarray.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
  char* string;
  int count;
  int size;
} mnstring;


char mnstring_is_greater(mnstring* str1,mnstring*str2);//tested
mnstring *mnarray_add_mnstring(mnarray *arr, mnstring *str);//tested
mnstring *mnarray_mnstring_at(mnarray *arr, size_t index);//tested
void mnarray_clean_mnstring(mnarray *arr);//tested
mnstring* mnstring_new();//tested
mnstring *mnstring_init(mnstring* str);
mnstring *mnstring_init_cstring_ref(mnstring *str,char *s);
mnstring *mnstring_init_cstring_cpy(mnstring *str,char *s);
mnstring *mnstring_clean(mnstring *str);
void mnstring_free_0(mnstring *str);
void mnstring_free(mnstring **str);//tested
mnstring* mnstring_clone(mnstring* str);//tested
char mnstring_is_equal(mnstring* str1,mnstring* str2);//tested
mnstring* mnstring_new_from_mnstring(mnstring *str);//tested
void *mnstring_new_from_mnstring_v0(void *s);//tested
void mnstring_free_v0(void* str);//tested
mnstring* mnstring_new_from_concat(int strings_count,...);//tested
mnstring* mnstring_new_from_int(int n);//tested
mnstring* mnstring_new_from_double(double d);//tested
mnstring* mnstring_new_concat_multi(const char* str,...);//tested
mnstring* mnstring_concat(mnstring* str_to,mnstring* str_sub);//tested
mnstring *mnstring_concat_msstr_cstr(mnstring *str_to,  char *str_sub);//tested
mnstring* mnstring_new_empty();//tested
char mnstring_is_empty(mnstring* str);//tested
mnstring *mnstring_new_from_array(mnarray *list);//tested
#ifdef __cplusplus
}
#endif



#endif // MNSTRING_H
