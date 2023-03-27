#pragma once
#include "mncstring.h"
#include "mnarray.h"
#include <stdio.h>
#include <string.h>

typedef mnarray mncstringList ;
mncstringList *mncstringList_new();//tested
mncstringList *mncstringList_init(mncstringList* str_list);//tested
void mncstringList_clean(mncstringList *str_list);//tested
void mncstringList_free(mncstringList ** str_list);//tested
void mncstringList_free_v0(mncstringList* str_list);//tested
void mncstringList_clean_free(mncstringList **str_list);//tested
char *mncstringList_add(mncstringList *str_list,  char* str);//tested
char *mncstringList_add_clone(mncstringList *str_list, const char *str);//tested
char* mncstringList_concat(mncstringList *str_list, char* end_line);//tested
size_t mncstringList_char_count(mncstringList* str_list);//tested
char* mncstringList_item_at(mncstringList* str_list, size_t index);//tested
//tested
// char* mnarray_add_cstring(mnarray* arr,char* str);//tested
// char* mnarray_cstring_at(mnarray* arr,size_t index);//tested
// void mnarray_clean_cstring(mnarray *arr);//tested
void mncstringList_printf(mncstringList* list);

#define TRASH mncstringList* __trash__ = mncstringList_init(0);
#define $(X) mncstringList_add(__trash__,X)
#define EMPTY_TRASH mncstringList_clean_free(&__trash__)