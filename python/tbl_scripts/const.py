lbl_name="name"
lbl_type="type"
lbl_must_not_nul="must_not_nul"
lbl_is_unique="is_unique"
lbl_is_primary_key="is_primary_key"
lbl_is_auto_inc="is_auto_inc"
lbl_default_val="default_val"
lbl_type_int="Int"
lbl_type_str="CString"
lbl_type_dbl="Double"
lbl_type_BINT="Big_int"
import datetime

table_name = "group"
lbl_fields_count =f"tbl{table_name}_fields_count"
today = datetime.date.today()
header = "tbl" + table_name + ".h"
source = "tbl" + table_name + ".c"
struct_meta_name = "tbl" + table_name + "_meta"
struct_meta_ptr = struct_meta_name + " *"
struct_record_name = "tbl" + table_name + "_record"
struct_record_ptr = struct_record_name + " *"
meta_param_name = "grp"
record_param_name = "record"
void_name = "void "
void_ptr_name = "void * "
struct_meta_ptr_hld = struct_meta_ptr + "*"
struct_record_ptr_hld = struct_record_ptr + "*"
# {lbl_name:"id",lbl_type:lbl_type_int,lbl_must_not_nul:1,lbl_is_auto_inc:0,lbl_default_val:None,lbl_is_primary_key:0,lbl_is_unique:0}
fields = [{lbl_name: "id", lbl_type: lbl_type_int, lbl_must_not_nul: 1, lbl_is_auto_inc: 1, lbl_default_val: 0,
           lbl_is_primary_key: 1, lbl_is_unique: 1},
          {lbl_name: "grp_name", lbl_type: lbl_type_str, lbl_must_not_nul: 1, lbl_is_auto_inc: 0, lbl_default_val: 0,
           lbl_is_primary_key: 0, lbl_is_unique: 0},
          {lbl_name: "can_login", lbl_type: lbl_type_int, lbl_must_not_nul: 1, lbl_is_auto_inc: 0, lbl_default_val: 1,
           lbl_is_primary_key: 0, lbl_is_unique: 0},
          {lbl_name: "can_edit_group", lbl_type: lbl_type_int, lbl_must_not_nul: 1, lbl_is_auto_inc: 0,
           lbl_default_val: 0, lbl_is_primary_key: 0, lbl_is_unique: 0}
          ]
fields_count=len(fields)
def intro():
    str1 = "//\n" + \
           "// Created by merhab on {today}.\n" + \
           "//\n""" + "#pragma once\n"
    return str1