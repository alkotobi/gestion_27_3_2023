#pragma once
#include "mnsystem.h"
#include <stdarg.h>
#include "mnarray.h"
#include <stdio.h>


#ifdef __cplusplus
extern "C"
{
#endif


size_t cstring_count(const char* str);//tested
size_t cstring_size(const char* str);//tested
char* cstring_new_v0(size_t size);//tested
char* cstring_new();//tested
char* cstring_new_fill_with_char(char character, size_t size);//tested
char* cstring_new_clone(const  char* str);//tested
char* str_cpy(char* str);
char* cstring_new_copy_with_char_count(const  char* str,int char_count);//tested
char cstring_is_equal(const char *str1,const char* str2);//tested
char* cstring_new_from_concat(int strings_count,...);//tested
char cstring_is_empty(const char* str);//tested
char *cstring_new_from_concat_v1(char ** str_list, size_t strings_count);//tested
char *cstring_new_concat_2(char* str1,char* str2);
char *cstring_new_from_concat_with_nl(char ** str_list,size_t strings_count);//tested
void cstring_free(void** str);//tested
void cstring_free_v0(void* str);//tested
char cstring_is_greater(const char *str1, const char *str2);//tested
void cstring_add_chars_can_err(char* str,char* chars);
void cstring_add(mnstrhld master_str, char *to_add_str);//tested
char* cstring_replace_sub_string_at(char* str,size_t ind,char* sub_str);//tested
char* mnarray_add_cstring_ref(mnarray* arr,char* str);//tested
char* mnarray_add_cstring_cpy(mnarray* arr,char* str);//tested
char* mnarray_cstring_at(mnarray* arr,size_t ind);//tested
void mnarray_clean_cstring(mnarray* arr);//tested
char* mnarray_search_first_cstring(mnarray* arr,char* str);//tested
char* mnarray_search_next_cstring(mnarray* arr,char* str);//tested
size_t cstring_find_sub(char* str,char* substr);
char* cstring_concat_multi(const char *str, ...);
char* str_concat(const char *str, ...);

#ifdef __cplusplus
}
#endif