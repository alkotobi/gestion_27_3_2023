from const import *


def source_intro():
    str0 = """//
// Created by merhab on {today}.
//\n"""
    return str0


def source_includes():
    str0 = "#include \"{}\"\n\n\n".format(header)
    return str0


def tbluser_meta_new():
    str0 = "{} {}_new(){{  \n".format(struct_meta_ptr, struct_meta_name) + \
           "    {} {}=({}) mnalloc(sizeof({}));\n".format(struct_meta_ptr, meta_param_name, struct_meta_ptr,
                                                          struct_meta_name) + \
           "    mnassert({});\n".format(meta_param_name) + \
           ''.join(["     {}->{}=0;\n".format(meta_param_name, d[lbl_name]) for d in fields]) + \
           "      {}->super.meta_list=0;\n}}\n".format(meta_param_name)
    return str0


def tbluser_meta_init():
    str0 = f"{struct_meta_ptr} {struct_meta_name}_init({struct_meta_ptr}{meta_param_name}) {{\n" + \
           f"if (!{meta_param_name}) {meta_param_name}= {struct_meta_name}_new();\n" + \
           f"{meta_param_name}->super.meta_list=mnarray_init_v0(0,{lbl_fields_count});\n" + \
           f"{meta_param_name}->super.table_name =\"{table_name}\";\n" + \
           "".join([f"{meta_param_name}->{d[lbl_name]}= mnmetadata_list_set_item_at({meta_param_name}->super.meta_list,"
                    f"\nmnmetadata_init(0,str_cpy(\"{d[lbl_name]}\"),"
                    f"{d[lbl_type]},{d[lbl_must_not_nul]},"
                    f"{d[lbl_is_unique]},\n{d[lbl_is_primary_key]},"
                    f"{d[lbl_is_auto_inc]},{d[lbl_default_val]}),{d[lbl_name].capitalize()});\n" for d in fields]) + \
           f"return {meta_param_name};\n}}\n"

    return str0


def tbluser_meta_free():
    str0 = f"{void_name} {struct_meta_name}_free({struct_meta_ptr_hld} {meta_param_name}_hld){{\n" \
           f"mnarray_free(&((*{meta_param_name}_hld)->super.meta_list));\n" \
           f"mnfree(*{meta_param_name}_hld);\n" \
           f"*{meta_param_name}_hld=0;\n" \
           f"}}\n"
    return str0


def tbluser_meta_clean_free():
    str0 = f"{void_name} {struct_meta_name}_clean_free({struct_meta_ptr_hld} {meta_param_name}_hld){{\n" \
           f" {struct_meta_name}_clean(*{meta_param_name}_hld);\n" \
           f" {struct_meta_name}_free({meta_param_name}_hld);\n" \
           f"}};\n"

    return str0


def tbluser_meta_clean():
    str0 = f"{struct_meta_ptr} {struct_meta_name}_clean({struct_meta_ptr} {meta_param_name}){{\n" \
           f"mnmetadata_list_clean({meta_param_name}->super.meta_list);\n"+ \
           "".join([f"{meta_param_name}->{d[lbl_name]}=0;\n" for d in fields]) + \
           f"return {meta_param_name};\n" \
           f"}}\n"
    return str0

def tbluser_record_init():
    str0=f"{struct_record_ptr} {struct_record_name}_init({struct_record_ptr} {record_param_name},"+\
        f",".join([f"mnvariant* {d[lbl_name]}\n"for d in fields])+f") {{\n"+\
        f"if (!{record_param_name}) {record_param_name}= {struct_record_name}_new();\n" \
        f"mnarray_init_v0(&{record_param_name}->var_list,{lbl_fields_count});\n" +\
        "".join([f"{record_param_name}->{d[lbl_name]}={d[lbl_name]};"
                 f"\nmnvariantList_set_item_at(&{record_param_name}->var_list,"
                 f"{record_param_name}->{d[lbl_name]},{d[lbl_name].capitalize()});\n"for d in fields])+\
        f"return {record_param_name};\n" \
        f"}}\n"

    return str0

def tbluser_record_refresh_list():
    str0=f"{struct_record_ptr} {struct_record_name}_refresh_list({struct_record_ptr} {record_param_name}){{\n" \
         f"mnvariantList_clean(&{record_param_name}->var_list);\n"+\
        "".join([f" mnvariantList_add(&{record_param_name}->var_list,{record_param_name}->{d[lbl_name]});\n" for d in fields])+\
        f"return {record_param_name};\n" \
        f"}}\n"
    return str0

def tbluser_record_new():
    str0=f"{struct_record_ptr} {struct_record_name}_new(){{\n" \
         f"{struct_record_ptr} {record_param_name}=({struct_record_ptr}) " \
         f"mnalloc(sizeof({struct_record_name}));\n" \
         f"mnassert({record_param_name});\n" +\
         f"".join([f"{record_param_name}->{d[lbl_name]}=0;\n" for d in fields]) +\
        f"return {record_param_name};\n" \
        f"}}\n"

    return str0

def tbluser_record_clean():
    str0=f"{struct_record_ptr} {struct_record_name}_clean({struct_record_ptr} {record_param_name}){{\n" \
         f"mnarray_clean(&{record_param_name}->var_list,(mnfree_fnc) mnvariant_clean_free);\n" +\
        f"".join([f"{record_param_name}->{d[lbl_name]}=0;\n"for d in fields]) +\
        f"return {record_param_name};\n" \
        f"}}\n"
    return str0

def tbluser_record_free():
    str0=f"{void_name} {struct_record_name}_free({struct_record_ptr_hld} {record_param_name}_hld){{\n" \
         f"mnfree(*{record_param_name}_hld);\n" \
         f"*{record_param_name}_hld=0;\n" \
         f"}}\n"
    return str0

def setters_def():
    str0="".join([f"{void_name} {struct_record_name}_set_{d[lbl_name]}"
                  f"({struct_record_ptr} {record_param_name},"
                  f"mnvariant* {d[lbl_name]}){{\n"
                  f"mnvariant_clean_free(&{record_param_name}->{d[lbl_name]});\n"
                  f"{record_param_name}->{d[lbl_name]}={d[lbl_name]};\n"
                  f"tbluser_record_refresh_list({record_param_name});\n"
                  f"}}\n" for d in fields])
    return str0
def tbluser_record_list_set_field_at():
    str0 =f"mnvariant * {struct_record_name}_list_set_field_at_clean_ex(" \
          f"{struct_record_ptr} {record_param_name},mnvariant *field,tbl{table_name}_fields_index ind){{\n" \
          f"mnvariantList* list= &{record_param_name}->var_list;\n" \
          f"list->array[ind] = field;\n" \
          f"switch (ind) {{\n"+\
        f"".join([f"case {d[lbl_name].capitalize()}:\n"
                  f"    {record_param_name}->{d[lbl_name]} = field;\n"
                  f"    break;\n"for d in fields])+\
        f"default:\n" \
        f"mnassert(0);\n" \
        f"}}\n" \
        f"return field;\n" \
        f"}}\n"

    return str0

def tbluser_record_list_set_field_at_clean_ex():
    str0 =f"mnvariant * {struct_record_name}_list_set_field_at_clean_ex(" \
          f"{struct_record_ptr} {record_param_name},mnvariant *field,tbl{table_name}_fields_index ind){{\n" \
          f"mnvariantList* list= &{record_param_name}->var_list;\n" \
          f"if (list->array[ind]) mnvariant_clean_free((mnvariant **) &list->array[ind]);\n" \
          f"list->array[ind] = field;\n" \
          f"switch (ind) {{\n"+ \
          f"".join([f"case {d[lbl_name].capitalize()}:\n"
                    f"    {record_param_name}->{d[lbl_name]} = field;\n"
                    f"    break;\n"for d in fields])+ \
          f"default:\n" \
          f"mnassert(0);\n" \
          f"}}\n" \
          f"return field;\n" \
          f"}}\n"

    return str0





