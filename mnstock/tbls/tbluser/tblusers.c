//
    // Created by merhab on {today}.
    //
#include "tblusers.h"


tblusers_meta * tblusers_meta_new(){  
    tblusers_meta * meta=(tblusers_meta *) mnalloc(sizeof(tblusers_meta));
    mnassert(meta);
     meta->id=0;
     meta->title=0;
     meta->login=0;
     meta->pass=0;
     meta->id_group=0;
      meta->super.meta_list=0;
return meta;
}
tblusers_meta * tblusers_meta_init(tblusers_meta *meta) {
if (!meta) meta= tblusers_meta_new();
meta->super.meta_list=mnarray_init_fill_with_0(0,tblusers_fields_count);
meta->super.table_name ="users";
meta->id= mnmetadata_list_set_item_at(meta->super.meta_list,
mnmetadata_init(0,str_cpy("id"),Int,1,1,
1,1,0),Id);
meta->title= mnmetadata_list_set_item_at(meta->super.meta_list,
mnmetadata_init(0,str_cpy("title"),CString,0,0,
0,0,0),Title);
meta->login= mnmetadata_list_set_item_at(meta->super.meta_list,
mnmetadata_init(0,str_cpy("login"),CString,0,0,
0,0,0),Login);
meta->pass= mnmetadata_list_set_item_at(meta->super.meta_list,
mnmetadata_init(0,str_cpy("pass"),CString,0,0,
0,0,0),Pass);
meta->id_group= mnmetadata_list_set_item_at(meta->super.meta_list,
mnmetadata_init(0,str_cpy("id_group"),Int,0,0,
0,0,0),Id_group);
return meta;
}
void  tblusers_meta_free(tblusers_meta ** meta_hld){
mnarray_free(&((*meta_hld)->super.meta_list));
mnfree(*meta_hld);
*meta_hld=0;
}
void  tblusers_meta_clean_free(tblusers_meta ** meta_hld){
 tblusers_meta_clean(*meta_hld);
 tblusers_meta_free(meta_hld);
};
tblusers_meta * tblusers_meta_clean(tblusers_meta * meta){
mnmetadata_list_clean(meta->super.meta_list);
meta->id=0;
meta->title=0;
meta->login=0;
meta->pass=0;
meta->id_group=0;
return meta;
}
tblusers_record * tblusers_record_init(tblusers_record * record,mnvariant* id
,mnvariant* title
,mnvariant* login
,mnvariant* pass
,mnvariant* id_group
) {
if (!record) record= tblusers_record_new();
mnarray_init_fill_with_0(&record->super.var_list,tblusers_fields_count);
record->id=id;
mnvariantList_set_item_at(&record->super.var_list,record->id,Id);
record->title=title;
mnvariantList_set_item_at(&record->super.var_list,record->title,Title);
record->login=login;
mnvariantList_set_item_at(&record->super.var_list,record->login,Login);
record->pass=pass;
mnvariantList_set_item_at(&record->super.var_list,record->pass,Pass);
record->id_group=id_group;
mnvariantList_set_item_at(&record->super.var_list,record->id_group,Id_group);
return record;
}
tblusers_record * tblusers_record_new(){
tblusers_record * record=(tblusers_record *) mnalloc(sizeof(tblusers_record));
mnassert(record);
record->id=0;
record->title=0;
record->login=0;
record->pass=0;
record->id_group=0;
record->super.var_list_set_field_at_clean_ex=tblusers_record_list_set_field_at_clean_ex;
return record;
}
tblusers_record * tblusers_record_clean(tblusers_record * record){
mnarray_clean(&record->super.var_list,(mnfree_fnc) mnvariant_clean_free);
record->id=0;
record->title=0;
record->login=0;
record->pass=0;
record->id_group=0;
return record;
}
void  tblusers_record_free(tblusers_record ** record_hld){
mnfree(*record_hld);
*record_hld=0;
}
void  tblusers_record_set_id(tblusers_record * record,mnvariant* id,char will_make_dirty){
mnvariant_clean_free(&record->id);
record->id=id;
tblusers_record_list_set_field_at(record,id,Id);
if (will_make_dirty) id->is_dirty = 1;
}
void  tblusers_record_set_title(tblusers_record * record,mnvariant* title,char will_make_dirty){
mnvariant_clean_free(&record->title);
record->title=title;
tblusers_record_list_set_field_at(record,title,Title);
if (will_make_dirty) title->is_dirty = 1;
}
void  tblusers_record_set_login(tblusers_record * record,mnvariant* login,char will_make_dirty){
mnvariant_clean_free(&record->login);
record->login=login;
tblusers_record_list_set_field_at(record,login,Login);
if (will_make_dirty) login->is_dirty = 1;
}
void  tblusers_record_set_pass(tblusers_record * record,mnvariant* pass,char will_make_dirty){
mnvariant_clean_free(&record->pass);
record->pass=pass;
tblusers_record_list_set_field_at(record,pass,Pass);
if (will_make_dirty) pass->is_dirty = 1;
}
void  tblusers_record_set_id_group(tblusers_record * record,mnvariant* id_group,char will_make_dirty){
mnvariant_clean_free(&record->id_group);
record->id_group=id_group;
tblusers_record_list_set_field_at(record,id_group,Id_group);
if (will_make_dirty) id_group->is_dirty = 1;
}
mnvariant * tblusers_record_list_set_field_at_clean_ex(void  *record_,mnvariant *field,char ind){
tblusers_record * record = record_;
mnvariantList* list= &record->super.var_list;
if (list->array[ind]) mnvariant_clean_free((mnvariant **) &list->array[ind]);
list->array[ind] = field;
switch (ind) {
case Id:
    record->id = field;
    break;
case Title:
    record->title = field;
    break;
case Login:
    record->login = field;
    break;
case Pass:
    record->pass = field;
    break;
case Id_group:
    record->id_group = field;
    break;
default:
mnassert(0);
}
return field;
}
mnvariant * tblusers_record_list_set_field_at(tblusers_record * record,mnvariant *field,tblusers_fields_index ind){
mnvariantList* list= &record->super.var_list;
list->array[ind] = field;
switch (ind) {
case Id:
    record->id = field;
    break;
case Title:
    record->title = field;
    break;
case Login:
    record->login = field;
    break;
case Pass:
    record->pass = field;
    break;
case Id_group:
    record->id_group = field;
    break;
default:
mnassert(0);
}
return field;
}
