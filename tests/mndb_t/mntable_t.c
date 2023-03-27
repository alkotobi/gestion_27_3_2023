//
// Created by merhab on 2023/3/20.
//
#include "mntable_t.h"

char mntable_test() {
    mnmetadata_list* meta_list = mnmetadata_list_init(0);
    mnmetadata_list_add(meta_list,mnmetadata_init(0,"name",0,1,1,1,1,0));

    mndatabase* db= mndatabase_init(0, SQLITE, mnsqlite_param_init_ref(0, 0, 0, NULL));

    //mnsql* sqlf = mnsqin
    return 0;
}
