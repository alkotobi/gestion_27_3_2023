//
// Created by merhab on 2023/3/20.
//
#include <stdio.h>
#include "mncstringList.h"
#include "mnsql.h"
#include "mnfilter.h"
#include "mndatabase.h"



int main(int argc, char const *argv[]){
    mnfilter* filter = 0;
    mnmetadata_list* meta = mnmetadata_list_init(0);
    mnmetadata* md=mnmetadata_init(0,"nour",Int,1,1,1,1,0);
    filter= mnfilter_init(0, 0, md->name, EQ, NULL);
    mnmetadata_list_add(meta,md );
    md=mnmetadata_init(0,"ism",CString,1,1,0,0, mnvariant_init_cstring(0,str_cpy("kiss")));
    filter = mnfilter_init(0, AND_NOT, md->name, EQ, NULL);
    mnmetadata_list_add(meta, md);
    char* str = mnsql_create_table_v0("user",meta);
    printf("%s", str);
    printf("\n");
    printf("%s", mnfilter_create_with_params(filter));
    mnfilter_clean_free(&filter);
    mndatabase *db = mndatabase_init(0, SQLITE, mnsqlite_param_init_ref(0, 0, 0, str_cpy("tbls.sqslite")));
    //tbluser_meta * user_meta = tbluser_meta_new() ;
    //mndatabase_exec(tbls, mnsql_create_table_v1(tbluser_meta_init(0)->super));

}


