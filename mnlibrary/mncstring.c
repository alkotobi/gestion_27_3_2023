#include "mncstring.h"

size_t cstring_count(const char *str)
{
    if (!str) {
        return 0;
    }
    size_t j;j=0;
    for(;;){
        if(str[j]=='\0'){
            break;
        }
        j++;
    }
    return j;
}

size_t cstring_size(const char* str){
    return cstring_count(str)+1;
}

char* cstring_new_v0(size_t size){
    char* str = (char*)mncalloc((size+1),sizeof (char));
    mnassert(str);
    return str;
}

char* cstring_new()
{
    return cstring_new_v0(ARRAY_MIN_SIZE);
}

char* cstring_new_fill_with_char(char character,size_t size){
    char* str = cstring_new_v0(size);
    str[size]=0;
    for (size_t i=0;i<size;i++) {
        str[i]=character;

    }
    return str;
}



char *cstring_new_clone(const  char *str)
{
    if (!str) {
        return 0;
    }
    int size=cstring_size(str);
    char* str2=malloc(sizeof (char)*size);
    assert(str2);
    for(int i=0;str[i]!=0;i++){
        str2[i]=str[i];

    }
    str2[size-1]=0;
    return str2;
}
char* str_cpy(char* str){
    return cstring_new_clone(str);
}
char *cstring_new_copy_with_char_count(const char *str, int char_count)
{
    mnassert((void*)str);
    char* str2=mnalloc(sizeof (char)*(char_count+1));
    for(int i=0;i<char_count;i++){
        if (str[i]==0)
        {
            break;
        }
        
        str2[i]=str[i];

    }
    str2[char_count]=0;
    return str2;
}

char cstring_is_equal(const char *str1, const char *str2)
{
    int count1= cstring_count(str1);
    int count2= cstring_count(str2);
    if (count1!=count2){
        return 0;
    }
    for (int i=0;i<count1 ;i++ ) {
        if(str1[i]!=str2[i]){
            return 0;
        }
    }
    return 1;
}
char *cstring_new_from_concat_with_nl(char ** str_list,size_t strings_count){
    size_t count=0;
    for (size_t i=0; i < strings_count; i++)
    {
        count = count+cstring_count(str_list[i]);
    }
    char* str=malloc(sizeof(char)*((count+1)+strings_count));
    int j=0;

    for (size_t i=0; i < strings_count; i++)
    {
        char* s=str_list[i];
        for (int i=0;s[i]!=0 ;i++ ) {
            str[j]=s[i];
            j++;
        }
        str[j]='\n';
        j++;
    }
    str[j]=0;
    return str;
}
char *cstring_new_from_concat_v1(char ** str_list,size_t strings_count){
    size_t count=0;
    for (size_t i=0; i < strings_count; i++)
    {
        count = count+cstring_count(str_list[i]);
    }
    char* str=malloc(sizeof(char)*(count+1));
    int j=0;

    for (size_t i=0; i < strings_count; i++)
    {
        char* s=str_list[i];
        for (size_t k=0;s[k]!=0 ;k++ ) {
            str[j]=s[k];
            j++;
        }
    }
    str[j]=0;
    return str;
}
char *cstring_new_concat_2(char* str1,char* str2){
    return cstring_new_from_concat(2,str1,str2);
}
char *cstring_new_from_concat(int strings_count,...)
{
    va_list L;
    int count = 0;
    va_start(L, strings_count);
    for (int i=0; i < strings_count; i++)
    {
        count = count+cstring_count(va_arg(L, char*));
    }

    va_end(L);
    char* str=malloc(sizeof(char)*(count+1));
    int j=0;
    va_start(L, strings_count);

    for (int i=0; i < strings_count; i++)
    {
        char* s=va_arg(L, char*);
        for (size_t k=0;s[k]!=0 ;k++ ) {
            str[j]=s[k];
            j++;
        }
    }
    str[j]=0;
    va_end(L);
    return str;
}

char cstring_is_empty(const char *str)
{
    return cstring_is_equal(str,"");
}

void cstring_free(void **str)
{
    mnfree(*str);
    *str=0;
}

void cstring_free_v0(void* str){
    mnfree(str);
}

char cstring_is_greater(const char *str1, const char *str2)
{
    int len1=cstring_count(str1);
    int len2=cstring_count(str2);
    int len = len1<len2? len1:len2;
    for (int i =0;i<len ;i++ ) {
        if (str1[i]==str2[i]) {
            continue;
        }
        if(str1[i]<str2[i]) {
            return 0;
        }else{
            return 1;
        }
    }
    return 0;
}

void cstring_add_chars_can_err(char* str,char* chars){
    //TODO: cstring_add_chars redesign to avoid errors
    size_t str_count=cstring_count(str);
    size_t chars_count = cstring_count(chars);
    size_t j=0;
    size_t i = str_count;
    size_t count= str_count+chars_count;
    for (;i<count;i++ ) {
        str[i]=chars[j];
        j++;
    }
    str[i]=0;

}


void cstring_add(mnstrhld master_str, char* to_add_str){
    //TODO: test cstring_add
    size_t size1= cstring_count(*master_str);
    size_t size2= cstring_count(to_add_str);
    char* str=cstring_new_v0(size1+size2);
    size_t j = 0;
    for (; j < size1; j++) {
        str[j]=(*master_str)[j];
    }
    for (size_t i = 0; i < size2; ++i) {
        str[j]=to_add_str[i];
        j++;
    }
    str[j]=0;

    *master_str =str;

}

char* cstring_replace_sub_string_at(char* str,size_t ind,char* sub_str){
    size_t count=cstring_count(str);
    if (ind>=count)
    {
        mnassert(0);
    }
    size_t j=0;
    for (size_t i = ind; i < count; i++)
    {
        if (sub_str[j]==0)
        {
            break;
        }
        str[i]=sub_str[j];
        j++;
        
    }
    return str;
    
}

char* mnarray_add_cstring_ref(mnarray* arr,char* str)
{
    mnarray_add(arr,str);
    return str;
}

char* mnarray_add_cstring_cpy(mnarray* arr,char* str)
{
    char* s=cstring_new_clone(str);
    mnarray_add_cstring_ref(arr,s);
    return s;

}

char* mnarray_cstring_at(mnarray* arr,size_t ind)
{
    return (char*) mnarray_item_at(arr,ind);
}

void mnarray_clean_cstring(mnarray* arr)
{
    mnarray_clean(arr,cstring_free);
}

char* mnarray_search_first_cstring(mnarray* arr,char* str)
{
    return (char*)mnarray_search_first(arr,str,(mnf_char_var_var)cstring_is_equal);
}

char* mnarray_search_next_cstring(mnarray* arr,char* str)
{
    return (char*)mnarray_search_next(arr,str,(mnf_char_var_var)cstring_is_equal);
}

size_t cstring_find_sub(char *str, char *substr) {
    int i, j, flag;
    size_t str_len = cstring_count(str);
    size_t substr_len = cstring_count(substr);
    for(i=0; i<=str_len-substr_len; i++)
    {
        flag = 1;
        for(j=0; j<substr_len; j++)
        {
            if(str[i+j] != substr[j])
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            return i;
        }
    }

    return -1;
}



char* cstring_concat_multi(const char *str, ...){
    //TODO: recheck cstring_concat_multi
    va_list args;
    va_start(args, str);
    size_t len = vsnprintf(NULL, 0, str, args);
    char* s =  cstring_new_v0(len);
    va_end(args);
    va_start(args, str);
    vsprintf(s, str, args);
    va_end(args);
    return s;
    }






