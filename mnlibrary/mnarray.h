#pragma once
#include "mnsystem.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct 
{
    size_t size;
    size_t count;
    size_t index;
    mnptrhld array;
}mnarray;

mnarray* mnarray_new();//tested
mnarray* mnarray_init_v0(mnarray* array,size_t size);//tested
mnarray* mnarray_init_fill_with_0(mnarray* array,size_t size);
mnarray* mnarray_init(mnarray* array);//not tested
void mnarray_free(mnarray** array);//tested
void mnarray_free_v0(mnarray* arr);//tested
void mnarray_clean_free(mnarray **arr,mnf_void_ptrhld free_me);
void* mnarray_add(mnarray* arr,void* data_ptr);//tested
void* mnarray_remove_ref(mnarray* arr,size_t ind);//tested

mnarray* mnarray_clean(mnarray* arr,mnfree_fnc f);//tested
void* mnarray_item_at(mnarray* arr,size_t ind);//tested
size_t mnarray_count(mnarray* arr);//tested
mnarray* mnarray_clone(mnarray* arr,mnf_var_var clone_me);//tested
char mnarray_eof(mnarray* arr);//tested
char mnarray_bof(mnarray* arr);//tested
void* mnarray_first(mnarray* arr);//tested
void* mnarray_current(mnarray* arr);//tested
void* mnarray_next(mnarray* arr);//tested
void* mnarray_prior(mnarray* arr);//tested
void* mnarray_last(mnarray* arr);//tested
size_t mnarray_search_first(mnarray* arr,void* val_to_search,mnf_char_var_var is_equal);//tested
size_t mnarray_search_next(mnarray* arr,void* val_to_search,mnf_char_var_var is_equal);//tested
char mnarray_is_equal(mnarray *arr1,mnarray *arr2,mnf_char_var_var is_equal);//tested
mnarray* mnarray_add_array(mnarray* main_arr,mnarray* to_be_added_arr);
size_t mnarray_get_index_of_item(mnarray* arr,void* item);


#ifdef __cplusplus
}
#endif
