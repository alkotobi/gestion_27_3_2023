#include "mnarray.h"



mnarray *mnarray_new()
{
    mnarray* arr=(mnarray*) mnalloc(sizeof(mnarray));
    arr->array=0;
    arr->count=0;
    arr->index=-1;
    arr->size=0;
    return arr;

}

mnarray* mnarray_clean(mnarray *arr, mnfree_fnc f)
{
    mnassert(arr);
    for (size_t i = 0; i < arr->count; i++)
    {
        f(&(arr->array[i]));
        arr->array[i]=0;
    }
    arr->count=0;
    return arr;
}

mnarray* mnarray_init_v0(mnarray* array,size_t size)
{
    if (!array)
    {
        array = mnarray_new();
    }
    array->size=size;
    array->count=0;
    array->index=0;
    array->array=(void**) mnalloc(sizeof(void*)*size);
    mnassert(array->array);
    return array;
}

mnarray* mnarray_init(mnarray* array)
{
    return mnarray_init_v0(array,ARRAY_MIN_SIZE);
}

void mnarray_free(mnarray** array)
{
    mnfree((*array)->array);
    mnarray_free_v0(*array);
    *array =0;
}

void mnarray_free_v0(mnarray* arr)
{
    mnfree((arr));
}

void mnarray_clean_free(mnarray **arr,mnf_void_ptrhld free_me)
{
    mnarray_clean(*arr,free_me);
    mnarray_free(arr);
}

void* mnarray_add(mnarray* arr,void* data_ptr)
{
    mnassert(data_ptr);
    mnassert(arr);
    if (arr->count==arr->size)
    {
        arr->array=(void**)mnrealloc(arr->array,(sizeof(void*))* arr->size*2);
        arr->size=arr->size*2;
    }
    arr->array[arr->count]=data_ptr;
    arr->count++;
    return data_ptr;
}

void* mnarray_remove_ref(mnarray* arr,size_t ind)
{
    mnassert(arr);
    if(ind >= arr->count) mnassert(0);
    void* ret = arr->array[ind];
    for (size_t i = ind; i < arr->count-1; i++)
    {
        arr->array[i]=arr->array[i+1];
    }
    arr->array[arr->count-1]=0;
    arr->count--;    
    return ret;
}


void* mnarray_item_at(mnarray* arr,size_t ind)
{
    mnassert(arr);
    if(!(ind<arr->count)){
        mnassert(0);
    }
    return arr->array[ind];
}

size_t mnarray_count(mnarray *arr)
{
    mnassert(arr);
    return arr->count;
}

mnarray* mnarray_clone(mnarray* arr,mnf_var_var clone_me)
{
    mnassert(arr);
    mnarray* array = mnarray_init_v0(mnarray_new(),arr->size);
    for (size_t i = 0; i < arr->count; i++)
    {
        array->array[i]=clone_me(mnarray_item_at(arr,i));
    }
    array->count=arr->count;
    return array;    

}

char mnarray_eof(mnarray* arr)
{
    return arr->index== (arr->count-1);
}

char mnarray_bof(mnarray* arr)
{
    return (char)(arr->index==0);
}


void* mnarray_first(mnarray* arr)
{
    arr->index=0;
    return mnarray_current(arr);
}

void* mnarray_current(mnarray* arr)
{
    return mnarray_item_at(arr,arr->index);
}

void* mnarray_next(mnarray* arr)
{
    if (!mnarray_eof(arr))
    {
        arr->index++;

    }
    return mnarray_current(arr);
    
}

void* mnarray_prior(mnarray* arr)
{
       if (!mnarray_bof(arr))
    {
        arr->index--;

    }
    return mnarray_current(arr); 
}

void* mnarray_last(mnarray* arr)
{
    arr->index=arr->count-1;
    return mnarray_current(arr);    
}

size_t mnarray_search_first(mnarray* arr,void* val_to_search,mnf_char_var_var is_equal)
{
    for (size_t i = 0; i < arr->count; i++)
    {
        if (is_equal(mnarray_item_at(arr,i),val_to_search))
        {
            arr->index=i;
            return i;
        }

        
    }
    return -1;
    
}

size_t mnarray_search_next(mnarray* arr,void* val_to_search,mnf_char_var_var is_equal)
{
    if (mnarray_eof(arr))
    {
        return -1;
    }
    
     for (size_t i = arr->index+1; i < arr->count; i++)
    {
        if (is_equal(mnarray_item_at(arr,i),val_to_search))
        {
            arr->index=i;
            return i;
        }
        
        
    }   
    return -1;
}

char mnarray_is_equal(mnarray *arr1,mnarray *arr2,mnf_char_var_var is_equal)
{
    if (arr1->count!=arr2->count)
    {
        return 0;
    }
    
    for (size_t i = 0; i < arr1->count; i++)
    {
        if (!is_equal(arr1->array[i],arr2->array[i]))
        {
            return 0;
        }
        
    }

    return 1;
    
}

mnarray* mnarray_concat_to_new_array(mnarray* arr1,mnarray* arr2){
    mnarray* arr = mnarray_init(0);
    for (size_t i = 0; i < arr1->count ; ++i) {
        mnarray_add(arr, mnarray_item_at(arr1,i));
    }
    for (size_t i = 0; i < arr2->count ; ++i) {
        mnarray_add(arr, mnarray_item_at(arr2,i));
    }
    return arr;
}
mnarray *mnarray_add_array(mnarray *main_arr, mnarray *to_be_added_arr) {
    for (size_t i = 0; i < to_be_added_arr->count; ++i) {
        mnarray_add(main_arr, mnarray_item_at(to_be_added_arr,i));
    }
    return main_arr;
}

size_t mnarray_get_index_of_item(mnarray *arr, void *item) {
    for (size_t i = 0; i <arr->count ; ++i) {
        if (mnarray_item_at(arr,i)==item){
            return i;
        }
    }
    return -1;
}

mnarray *mnarray_init_fill_with_0(mnarray *array, size_t size) {
    array=mnarray_init_v0(array,size);
    for (size_t i = 0; i <array->size ; ++i) {
        array->array[i]=0;
    }
    return array;
}

