//
// Created by merhab on 2023/3/26.
//
#include "mndataset_t.h"

char mndataset_t() {
    mndataset* dataset = mndataset_new();
    test(1,"create mndataset...\n");
    tblusers_meta* user_meta= tblusers_meta_init(0);
    test(1,"create tbluser_meta...\n");
    mnsqlite_param* db_param= mnsqlite_param_init_cpy(0, 0, 0, "/Users/merhab/Desktop/db_tests/example0.sqlite");
    test(1,"create mnsqlite_param...\n");
    mndatabase* db = mndatabase_init(0, SQLITE, db_param);
    test(1,"create mndatabase...\n");
    mncstringList* fld_names_list= mnmetadata_list_fld_names_list_cpy(user_meta->super.meta_list, 0);
    char*fld_names=mnsql_sql_fields(fld_names_list);
    mnsql* sqlm = mnsql_init_v0(0,db->driver,user_meta->super.table_name,user_meta->super.meta_list,0);
    test(1,"create mnsql...\n");
    mndataset_init(dataset, (tbl_super *) user_meta, db, sqlm);
    mndataset_create_table(dataset);
    test(1,"testing mndataset_create_table...\n");
    tblusers_record * rec=tblusers_record_init(0, VAR_I(1), VAR_S("nour"),
                                             VAR_S("noor"), VAR_S("123"), VAR_BI(-1));
    mnvariantList_printf(&(rec->super.var_list));
    size_t ind=mndataset_insert_v0(dataset,&(rec->super));
//    for (int i = 0; i <10 ; ++i) {
//        tblusers_record * r= tblusers_record_init(0, VAR_I(1), VAR_S(str_concat("ana%d",i)),VAR_S(str_concat("howa%d",i)),VAR_S(str_concat("grp%d",i)),
//                            VAR_I(i));
//        mndataset_insert_v0(dataset,&r->super);
//    }
    tblusers_record_set_id(rec,VAR_I(6));
    //rec->id= VAR_I(6);
    tblusers_record_set_title(rec,VAR_S(str_cpy("tototo")));
//    rec->title= str_cpy("tototo");
    mndataset_update(dataset,rec);
    //mndataset_get_data(dataset);
//    for (size_t i = 0; i <dataset->recordset->count ; ++i) {
//        mnvariantList_printf(mnarray_item_at(dataset->recordset,i));
//        printf("\n");
//
//    }
    //rec->id= VAR_BI(ind);
    //tbluser_record_refresh_list(rec);
    //mnrecordset_add(dataset->recordset, (mnrecord *) rec);

    return 1;
}

