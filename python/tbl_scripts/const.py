from fields import *
lbl_name = "name"
lbl_type = "type"
lbl_must_not_nul = "must_not_nul"
lbl_is_unique = "is_unique"
lbl_is_primary_key = "is_primary_key"
lbl_is_auto_inc = "is_auto_inc"
lbl_default_val = "default_val"
lbl_type_int = "Int"
lbl_type_str = "CString"
lbl_type_dbl = "Double"
lbl_type_BINT = "Big_int"
import datetime

meta_param_name = "meta"
record_param_name = "record"
void_name = "void "
void_ptr_name = "void * "
today = datetime.date.today()


# {lbl_name:"id",lbl_type:lbl_type_int,lbl_must_not_nul:1,lbl_is_auto_inc:0,lbl_default_val:None,lbl_is_primary_key:0,lbl_is_unique:0}


#
def intro():
    str1 = "//\n" + \
           "// Created by merhab on {today}.\n" + \
           "//\n""" + "#pragma once\n"
    return str1


class User_Input:
    def __init__(self):
        self.table_name = ""
        self.fields = []

    # table_name = "group"
    def get_lbl_fields_count(self):
        return f"tbl{self.table_name}_fields_count"

    def get_header(self):
        return "tbl" + self.table_name + ".h"

    def get_source(self):
        return "tbl" + self.table_name + ".c"

    def get_struct_meta_name(self):
        return "tbl" + self.table_name + "_meta"

    def get_struct_meta_ptr(self):
        return self.get_struct_meta_name() + " *"

    def get_struct_record_name(self):
        return "tbl" + self.table_name + "_record"

    def get_struct_record_ptr(self):
        return self.get_struct_record_name() + " *"

    def get_struct_meta_ptr_hld(self): return self.get_struct_meta_ptr() + "*"

    def get_struct_record_ptr_hld(self):
        return self.get_struct_record_ptr() + "*"

    def get_fields_count(self): return len(self.fields)

    def get_user_input(self):
        if table_name != "":
            self.table_name =table_name
            self.fields =fields
            return
        fld = []
        self.table_name = input("What is your TABLE name? \n")
        print("will start to get ur fields...\n")
        while True:
            dic = {}
            field_name = input("What is your FIELD name? or tape ENTER to exit\n")
            if field_name == '': break
            dic[lbl_name] = field_name
            tp = ""
            while not (tp.isalnum() and int(tp) in [1, 2, 3]):
                print("what is the TYPE of ur FIELD?\n"
                      "     for INT press    1\n"
                      "     for STR press    2\n"
                      "     for DOUBLE press 3\n")
                tp = input("")
            if tp == "1":
                dic[lbl_type] = lbl_type_int
            elif tp == "2":
                dic[lbl_type] = lbl_type_str
            elif tp == "3":
                dic[lbl_type] = lbl_type_dbl
            default = input("what is the default value of the field? enter for null\n")
            if default == "":
                dic[lbl_default_val] = 0
            else:
                dic[lbl_default_val] = default
            for s in [lbl_must_not_nul, lbl_is_auto_inc, lbl_is_unique, lbl_is_primary_key]:
                default = input(f"{s} enter for true , anything else for false\n")
                if default == "":
                    dic[s] = 1
                    print(f"{s}= TRUE\n")
                else:
                    dic[s] = 0
                    print(f"{s}= FALSE\n")
            fld.append(dic)
        self.fields = fld

        str0 = f"fields = [" + ",".join(
            [f"{{'{lbl_name}': '{d[lbl_name]}','{lbl_type}':'{d[lbl_type]}','{lbl_must_not_nul}':{d[lbl_must_not_nul]},"
             f"'{lbl_is_auto_inc}':{d[lbl_is_auto_inc]},'{lbl_default_val}':{d[lbl_default_val]},"
             f"'{lbl_is_primary_key}':{d[lbl_is_primary_key]},'{lbl_is_unique}':{d[lbl_is_unique]} }}\n" for d in self.fields]) + \
               "]\n" \
               f"table_name = '{self.table_name}'"

        try:
            with open('fields.py', 'w', encoding='utf-8') as file:
                contents = file.write(str0)
        except Exception as e:
            print(f"Error reading file: {e}")
