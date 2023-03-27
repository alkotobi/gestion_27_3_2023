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
    return grp;
}
tblgroup_meta * tblgroup_meta_init(tblgroup_meta *grp) {
    if (!grp) grp= tblgroup_meta_new();
    grp->super.meta_list=mnarray_init_v0(0,tblgroup_fields_count);
    grp->super.table_name ="group";
    grp->id= mnmetadata_list_set_item_at(grp->super.meta_list,
                                         mnmetadata_init(0,str_cpy("id"),Int,1,1,
                                                         1,1,0),Id);
    grp->grp_name= mnmetadata_list_set_item_at(grp->super.meta_list,
                                               mnmetadata_init(0,str_cpy("grp_name"),CString,1,0,
                                                               0,0,0),Grp_name);
    grp->can_login= mnmetadata_list_set_item_at(grp->super.meta_list,
                                                mnmetadata_init(0,str_cpy("can_login"),Int,1,0,
                                                                0,0,0),Can_login);
    grp->can_edit_group= mnmetadata_list_set_item_at(grp->super.meta_list,
                                                     mnmetadata_init(0,str_cpy("can_edit_group"),Int,1,0,
                                                                     0,0,0),Can_edit_group);
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
    mnarray_init_v0(&record->super.var_list,tblgroup_fields_count);
    record->id=id;
    mnvariantList_set_item_at(&record->super.var_list,record->id,Id);
    record->grp_name=grp_name;
    mnvariantList_set_item_at(&record->super.var_list,record->grp_name,Grp_name);
    record->can_login=can_login;
    mnvariantList_set_item_at(&record->super.var_list,record->can_login,Can_login);
    record->can_edit_group=can_edit_group;
    mnvariantList_set_item_at(&record->super.var_list,record->can_edit_group,Can_edit_group);
    return record;
}
void  tblgroup_record_refresh_list(void  *record_){
    tblgroup_record * record = (tblgroup_record *)record_;
    mnvariantList_clean(&record->super.var_list);
    mnvariantList_add(&record->super.var_list,record->id);
    mnvariantList_add(&record->super.var_list,record->grp_name);
    mnvariantList_add(&record->super.var_list,record->can_login);
    mnvariantList_add(&record->super.var_list,record->can_edit_group);
}
tblgroup_record * tblgroup_record_new(){
    tblgroup_record * record=(tblgroup_record *) mnalloc(sizeof(tblgroup_record));
    mnassert(record);
    record->id=0;
    record->grp_name=0;
    record->can_login=0;
    record->can_edit_group=0;
    record->super.refresh_list=tblgroup_record_refresh_list;return record;
}
tblgroup_record * tblgroup_record_clean(tblgroup_record * record){
    mnarray_clean(&record->super.var_list,(mnfree_fnc) mnvariant_clean_free);
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
void  tblgroup_record_set_id(tblgroup_record * record,mnvariant* id){
    mnvariant_clean_free(&record->id);
    record->id=id;
    tblgroup_record_refresh_list(record);
}
void  tblgroup_record_set_grp_name(tblgroup_record * record,mnvariant* grp_name){
    mnvariant_clean_free(&record->grp_name);
    record->grp_name=grp_name;
    tblgroup_record_refresh_list(record);
}
void  tblgroup_record_set_can_login(tblgroup_record * record,mnvariant* can_login){
    mnvariant_clean_free(&record->can_login);
    record->can_login=can_login;
    tblgroup_record_refresh_list(record);
}
void  tblgroup_record_set_can_edit_group(tblgroup_record * record,mnvariant* can_edit_group){
    mnvariant_clean_free(&record->can_edit_group);
    record->can_edit_group=can_edit_group;
    tblgroup_record_refresh_list(record);
}
mnvariant * tblgroup_record_list_set_field_at_clean_ex(tblgroup_record * record,mnvariant *field,tblgroup_fields_index ind){
    mnvariantList* list= &record->super.var_list;
    if (list->array[ind]) mnvariant_clean_free((mnvariant **) &list->array[ind]);
    list->array[ind] = field;
    switch (ind) {
        case Id:
            record->id = field;
            break;
        case Grp_name:
            record->grp_name = field;
            break;
        case Can_login:
            record->can_login = field;
            break;
        case Can_edit_group:
            record->can_edit_group = field;
            break;
        default:
            mnassert(0);
    }
    return field;
}
mnvariant * tblgroup_record_list_set_field_at(tblgroup_record * record,mnvariant *field,tblgroup_fields_index ind){
    mnvariantList* list= &record->super.var_list;
    list->array[ind] = field;
    switch (ind) {
        case Id:
            record->id = field;
            break;
        case Grp_name:
            record->grp_name = field;
            break;
        case Can_login:
            record->can_login = field;
            break;
        case Can_edit_group:
            record->can_edit_group = field;
            break;
        default:
            mnassert(0);
    }
    return field;
}
