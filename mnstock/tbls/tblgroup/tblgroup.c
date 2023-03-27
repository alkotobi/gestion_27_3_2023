//
// Created by merhab on {today}.
//
#include "tblgroup.h"


tblgroup_meta * tblgroup_meta_new(){
    tblgroup_meta * grp=(tblgroup_meta *) mnalloc(sizeof(tblgroup_meta));
    mnassert(grp);
    grp->id=0;
    grp->grp_name=0;
    grp->can_login=0;
    grp->can_edit_group=0;
    grp->super.meta_list=0;
}
tblgroup_meta * tblgroup_meta_init(tblgroup_meta *grp) {
    if (!grp) grp= tblgroup_meta_new();
    grp->super.meta_list=mnmetadata_list_init(0);
    grp->super.table_name ="group";
    grp->id= mnmetadata_list_add(grp->super.meta_list,
                                 mnmetadata_init(0,str_cpy("id"),Int,1,1,
                                                 1,1,0));
    grp->grp_name= mnmetadata_list_add(grp->super.meta_list,
                                       mnmetadata_init(0,str_cpy("grp_name"),CString,1,0,
                                                       0,0,0));
    grp->can_login= mnmetadata_list_add(grp->super.meta_list,
                                        mnmetadata_init(0,str_cpy("can_login"),Int,1,0,
                                                        0,0,0));
    grp->can_edit_group= mnmetadata_list_add(grp->super.meta_list,
                                             mnmetadata_init(0,str_cpy("can_edit_group"),Int,1,0,
                                                             0,0,0));
    return grp;
}
void  tblgroup_meta_free(tblgroup_meta ** grp_hld){
    mnarray_free(&((*grp_hld)->super.meta_list));
    mnfree(*grp_hld);
    *grp_hld=0;
}
void  tblgroup_meta_clean_free(tblgroup_meta ** grp_hld){
    tblgroup_meta_clean(*grp_hld);
    tblgroup_meta_free(grp_hld);
};
tblgroup_meta * tblgroup_meta_clean(tblgroup_meta * grp){
    mnmetadata_list_clean(grp->super.meta_list);
    grp->id=0;
    grp->grp_name=0;
    grp->can_login=0;
    grp->can_edit_group=0;
    return grp;
}
tblgroup_record * tblgroup_record_init(tblgroup_record * record,mnvariant* id
        ,mnvariant* grp_name
        ,mnvariant* can_login
        ,mnvariant* can_edit_group
) {
    if (!record) record= tblgroup_record_new();
    mnvariantList_init(&record->var_list);
    record->id=id;
    mnvariantList_add(&record->var_list,record->id);
    record->grp_name=grp_name;
    mnvariantList_add(&record->var_list,record->grp_name);
    record->can_login=can_login;
    mnvariantList_add(&record->var_list,record->can_login);
    record->can_edit_group=can_edit_group;
    mnvariantList_add(&record->var_list,record->can_edit_group);
    return record;
}
tblgroup_record * tblgroup_record_refresh(tblgroup_record * record){
    mnvariantList_clean(&record->var_list);
    mnvariantList_add(&record->var_list,record->id);
    mnvariantList_add(&record->var_list,record->grp_name);
    mnvariantList_add(&record->var_list,record->can_login);
    mnvariantList_add(&record->var_list,record->can_edit_group);
    return record;
}
tblgroup_record * tblgroup_record_new(){
    tblgroup_record * record=(tblgroup_record *) mnalloc(sizeof(tblgroup_record));
    mnassert(record);
    record->id=0;
    record->grp_name=0;
    record->can_login=0;
    record->can_edit_group=0;
    return record;
}
tblgroup_record * tblgroup_record_clean(tblgroup_record * record){
    mnarray_clean(&record->var_list,(mnfree_fnc) mnvariant_clean_free);
    record->id=0;
    record->grp_name=0;
    record->can_login=0;
    record->can_edit_group=0;
    return record;
}
void  tblgroup_record_free(tblgroup_record ** record_hld){
    mnfree(*record_hld);
    *record_hld=0;
}
