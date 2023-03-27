#include "mnarray_t.h"


void free_int(void** i){
    free(*i);
    *i=0;
}
char mnarray_test()
{
    char c=1;
   mnarray* arr = mnarray_new();
   mnarray_init_v0(arr,1);
   print_cyan("testing mnarray\n");
   c=c*test(arr->size==1,"size is ok..."); 
   c=c*test(arr->count==0,"count is ok...");
   //c=c*test((char)(arr->array),"array allocated...");
   //*********
   print_yellow("add 2 items to the array...\n");
   int* i=(int*)malloc(sizeof(int));
   *i=5;
   mnarray_add(arr,i);
   i=(int*)malloc(sizeof(int));
   *i=3;
   mnarray_add(arr,i);
   c=c*test(arr->size==2,"size is ok..."); 
   c=c*test(mnarray_count(arr)==2,"count is ok...");
   int j=*(int*)(arr->array[0]);
   j=*(int*)(arr->array[1]);
   c=c*(*(int*)(mnarray_item_at(arr,0))==5);
   c=c*(*(int*)(mnarray_item_at(arr,1))==3);
   test(c,"array add 2 items and extend size is ok...");
   print_yellow("remove ref 2nd item from the array...\n");
   i= mnarray_remove_ref(arr,1);
   c=c*test(arr->size==2,"size is ok..."); 
   c=c*test(arr->count==1,"count is ok...");
   c=c*(*i==3);
   c=c*(*(int*)(arr->array[0])==5);
   c=c*(arr->array[1]==0);
   test(c,"remove ref is ok...");   
   mnarray_clean(arr,free_int);
   mnarray_free(&arr);
   print_yellow("testing mnarray_clone,mnarray_is_equal...\n");
   mnarray array;
   mnarray_init(&array);
   mnarray_add(&array,cstring_new_clone("ana"));
   mnarray_add(&array,cstring_new_clone("anta"));
   mnarray *arr1=mnarray_clone(&array, (mnf_var_var) cstring_new_clone);
   c=c*mnarray_is_equal(&array, arr1, (mnf_char_var_var) cstring_is_equal);
   mnarray_clean_free(&arr1,cstring_free);
   test(c,"mnarray_clone,mnarray_is_equal....are ok\n");
    mnarray_add(&array,cstring_new_clone("howa"));
    mnarray_last(&array);
    c=c*cstring_is_equal(mnarray_current(&array),"howa");
    test(c,"mnarray_last is ok \n");
    mnarray_prior(&array);
    c=c*cstring_is_equal(mnarray_current(&array),"anta");
    test(c,"mnarray_prior is ok \n");
    mnarray_first(&array);
    c=c*cstring_is_equal(mnarray_current(&array),"ana");
    test(c,"mnarray_first is ok \n");
    mnarray_next(&array);
    c=c*cstring_is_equal(mnarray_current(&array),"anta");
    test(c,"mna(rray_next is ok \n");
    mnarray_add(&array,cstring_new_clone("anta"));
    size_t ind= mnarray_search_first(&array,"anta",(mnf_char_var_var)cstring_is_equal);
    c=c*(ind==1);
    test(c,"mnarray_search_first is ok \n");
    ind= mnarray_search_next(&array,"anta",(mnf_char_var_var)cstring_is_equal);
    c=c*(ind==3);
    test(c,"mnarray_search_next is ok \n");
    mnarray_clean(&array,cstring_free);
   return c;
}
