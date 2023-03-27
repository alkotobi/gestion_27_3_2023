#include "mnstring.h"



mnstring *mnstring_new()
{
    mnstring *self=mnalloc(sizeof (mnstring));
    self->string=0;
    self->count=0;
    self->size=0;
    return self;
}

mnstring *mnstring_init(mnstring *str){

    return mnstring_init_cstring_ref(str,0);
    
}

mnstring *mnstring_init_cstring_ref(mnstring *str,char *s)
{
    if (!str)
    {
        str=mnstring_new();
    }
    if (!s)
    {
        str->string=cstring_new();
        str->size=ARRAY_MIN_SIZE;
        str->count=0;
        mnassert(str->string);  
        return str;
    }
    
    str->string=s;
    str->size=cstring_count(s);
    str->count=str->size;
    return str;    
}   

mnstring *mnstring_init_cstring_cpy(mnstring *str,char *s){
    mnassert(s);
    return mnstring_init_cstring_ref(str,cstring_new_clone(s));
}

mnstring *mnstring_clean(mnstring *str)
{
    cstring_free_v0(str->string);
    str->string=0;
    str->size=0;
    str->count=0;
    return str;
}

void mnstring_free_0(mnstring *str){
    mnfree(str);
}

void mnstring_free(mnstring **str)
{
    mnstring_free_0(*str);
    *str=0;
}

void mnstring_clean_free(mnstring **str_hld){
    mnstring_clean(*str_hld);
    mnstring_free(str_hld);
}

mnstring *mnstring_clone(mnstring *str)
{
    return mnstring_init_cstring_cpy(mnstring_new(),str->string);
}

char mnstring_is_equal(mnstring *str1, mnstring *str2)
{
    if (str1->count!=str2->count) {
        return 0;
    }
    for (int i=0;i<str1->count ;i++ ) {
        if (str1->string[i]!=str2->string[i]) {
            return 0;
        }
    }
    return 1;
}




void mnstring_free_v0(void* str){
    mnstring_free((mnstring**)&str);
}


mnstring *mnstring_new_from_mnstring(mnstring *str)
{
    mnassert(str);
    mnstring* mstring =mnstring_new();
    char* string =cstring_new_copy_with_char_count(str->string,str->count);
    mstring->string=string;
    mstring->count=str->count;
    mstring->size=str->count;
    return mstring;
}

void *mnstring_new_from_mnstring_v0(void *s)
{
    mnassert(s);
    mnstring* str=s;
    mnassert(s);
    mnstring* mstring =mnstring_new();
    char* string =cstring_new_copy_with_char_count(str->string,str->count);
    mstring->string=string;
    mstring->count=str->count;
    mstring->size=str->count;
    return mstring;
}


mnstring* mnstring_new_from_concat(int strings_count,...)
{
    va_list L;
    int count = 0;
    va_start(L, strings_count);
    for (int i=0; i < strings_count; i++)
    {
        mnstring* str=va_arg(L, mnstring*);
        count = count+(str->count);
    }

    va_end(L);
    mnstring* str=mnstring_init_cstring_ref(mnstring_new(),cstring_new_v0(count));
    int j=0;
    va_start(L, strings_count);

    for (int i=0; i < strings_count; i++)
    {
        char* s=va_arg(L, mnstring*)->string;
        for (size_t k=0;s[k]!=0 ;k++ ) {
            str->string[j]=s[k];
            j++;
        }
    }
    str->string[j]=0;
    str->count=count;
    str->size=count;
    va_end(L);
    return str;
}

mnstring* mnstring_new_from_int(int n){
    char str[500];
    sprintf(str,"%d",n);
    return mnstring_init_cstring_cpy(mnstring_new(),str);

}

mnstring* mnstring_new_from_double(double d){
    
    mnstring* s= mnstring_init_cstring_ref(mnstring_new(),cstring_new_v0(30));
    sprintf(s->string,"%f",d);
    return s;
}
mnstring* mnstring_new_concat_multi(const char *str,...){
    va_list ap;
    int i=0;
    int j=0;
    va_start(ap, str);
    char str1[250];
    mnarray* list =mnarray_init(mnarray_new());
    while(str[i]!='\0'){
        if(str[i]=='%'){
            str1[j]=0;
            mnarray_add_mnstring(list,mnstring_init_cstring_cpy(0,str1));
            i++;
            if(str[i]=='s'){
                mnarray_add_mnstring(list,mnstring_init_cstring_cpy(0,va_arg(ap, char*)));
            }
            else if(str[i]=='d'){
                mnarray_add_mnstring(list, mnstring_new_from_int(va_arg(ap, int)));
            }
            else if(str[i]=='m'){//for mnstring
                mnstring* ss= va_arg(ap, mnstring*);
                mnarray_add_mnstring(list,mnstring_clone(ss));
            }
            j=0;
            i++;
            continue;
        }
        str1[j]=str[i];
        j++;
        i++;
    }
    va_end(ap);
    str1[j]=0;
    mnarray_add_mnstring(list,mnstring_init_cstring_cpy(0,str1));
    mnstring*s=mnstring_new_from_array(list);
    mnarray_clean_mnstring(list);
    mnarray_free(&list);
    return  s;
}

mnstring* mnstring_concat(mnstring *str_to, mnstring *str_sub)
{
    int count=str_to->count+str_sub->count;
    int i=str_to->count;
    if(str_to->size<(count)){
        str_to->string=mnrealloc(str_to->string,sizeof (char)*(count+1));
        mnassert(str_to->string);
        str_to->size=count;
    }
    int j=0;
    for (;i<count ;i++ ) {
        str_to->string[i]=str_sub->string[j];
        j++;
    }
    str_to->string[count]=0;
    str_to->count=count;
    return str_to;
}

mnstring *mnstring_concat_msstr_cstr(mnstring *str_to,  char *str_sub)
{
    mnstring str;
    mnstring_init_cstring_ref(&str,str_sub);
    mnstring_concat(str_to,&str);
    return str_to;
}



mnstring *mnstring_new_empty()
{
    return mnstring_init_cstring_cpy(0,"");
}

char mnstring_is_empty(mnstring* str){
    return cstring_is_empty(str->string);
}

mnstring *mnstring_new_from_array(mnarray *list)
{

    int size=0;
    mnstring* str;
    for (size_t i=0;i<list->count ;i++ ) {
        //if (!meta_list->data[1])continue;
        size=size+(mnarray_mnstring_at(list,i)->count);
    }
    mnstring*s= mnstring_init_cstring_ref(0,cstring_new_v0(size));
    int j=0;
    for (size_t i=0;i<list->count ;i++ ) {
        //if (!meta_list->data[1])continue;
        str =mnarray_mnstring_at(list,i);
        for (int n=0;n<str->count ;n++ ) {
            s->string[j]=str->string[n];
            j++;
        }
    }
    s->string[j]=0;
    s->count=size;
    s->size=size;

    return s;
}



char mnstring_is_greater(mnstring* str1,mnstring*str2){
    return cstring_is_greater(str1->string,str2->string);
}



mnstring *mnarray_add_mnstring(mnarray *arr, mnstring *str)
{
    mnarray_add(arr,(void*)str);
    return str;
}

mnstring *mnarray_mnstring_at(mnarray *arr, size_t index)
{
    return (mnstring*)mnarray_item_at(arr,index);
}

void mnarray_clean_mnstring(mnarray *arr)
{
    mnarray_clean(arr,(mnf_void_ptrhld)mnstring_clean_free);
}
