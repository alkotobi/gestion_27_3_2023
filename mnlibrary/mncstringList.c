
#include "mncstringList.h"
#include <stdarg.h>


mncstringList* mncstringList_new()
{
    return mnarray_new();
}

mncstringList *mncstringList_init(mncstringList* str_list)
{
    return mnarray_init(str_list);
}

void mncstringList_clean(mncstringList* str_list){
    mnarray_clean(str_list,cstring_free);
}

void mncstringList_free(mncstringList** str_list)
{
    mnarray_free(str_list);
}

void mncstringList_free_v0(mncstringList* str_list)
{
    mnarray_free_v0(str_list);
}

void mncstringList_clean_free(mncstringList** str_list){
    mncstringList_clean(*str_list);
    mncstringList_free(str_list);
}

char* mncstringList_add(mncstringList* str_list, char* str)
{
    mnarray_add(str_list,str);
    return str;
}

char* mncstringList_add_clone(mncstringList* str_list,const char* str)
{
    char* _str =cstring_new_clone(str);
    mncstringList_add(str_list,_str);
    return _str;
}

char* mncstringList_concat(mncstringList *str_list, char* end_line)
{
    //TODO:test mncstringList_concat
    //TODO:redisgn
    size_t end_count=cstring_count(end_line);
    size_t end_lines_count=end_count*mnarray_count(str_list);
    size_t char_count=mncstringList_char_count(str_list);
    char* str =(char*) malloc(sizeof (char)*(end_lines_count+char_count+1));
    mnassert(str);
    size_t j=0;
    size_t count=char_count+end_lines_count;
    for (size_t n = 0; n <str_list->count ; n++)
    {
        char* s = mncstringList_item_at(str_list,n);
        if (s[0]==0){
            continue;
        }
        for (size_t i = 0; s[i]!=0; i++)
        {
            str[j]=s[i];
            j++;
        }
        for (size_t i = 0; end_line[i]!=0; i++)
        {
            str[j]=end_line[i];
            j++;
        }       
        
    }
    str[j]=0;

    return str;

}

size_t mncstringList_char_count(mncstringList *str_list)
{
    size_t char_count=0;
    for (size_t i=0;i<mnarray_count(str_list) ;i++ ) {
        char_count=char_count+ cstring_count(mncstringList_item_at(str_list,i));
    }
    return char_count;
}

char* mncstringList_item_at(mncstringList *str_list, size_t index)
{
    return (char*)mnarray_item_at(str_list,index);
}



void mncstringList_printf(mncstringList *list) {
    for (size_t i = 0; i <list->count ; ++i) {
        printf("%s",mncstringList_item_at(list,i));
        printf("\n");
    }
}

// char *mnarray_add_cstring(mnarray *arr, char *str)
// {
//     mnarray_add(arr,(void*)str);
//     return str;
// }

// char *mnarray_cstring_at(mnarray *arr, size_t index)
// {
//     return (char*)mnarray_item_at(arr,index);
// }

// void mnarray_clean_cstring(mnarray *arr)
// {
//     mnarray_clean(arr,cstring_free);
// }
