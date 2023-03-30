from const import *


class Source:
    def __init__(self, user_input):
        self.input = user_input

    @staticmethod
    def source_intro():
        str0 = """//
    // Created by merhab on {today}.
    //\n"""
        return str0

    def source_includes(self):
        str0 = "#include \"{}\"\n\n\n".format(self.input.get_header())
        return str0

    def tbluser_meta_new(self):
        str0 = "{} {}_new(){{  \n".format(self.input.get_struct_meta_ptr(), self.input.get_struct_meta_name()) + \
               "    {} {}=({}) mnalloc(sizeof({}));\n".format(self.input.get_struct_meta_ptr(), meta_param_name,
                                                              self.input.get_struct_meta_ptr(),
                                                              self.input.get_struct_meta_name()) + \
               "    mnassert({});\n".format(meta_param_name) + \
               ''.join(["     {}->{}=0;\n".format(meta_param_name, d[lbl_name]) for d in self.input.fields]) + \
               f"      {meta_param_name}->super.meta_list=0;\n" \
               f"return {meta_param_name};\n}}\n"
        return str0

    def tbluser_meta_init(self):
        str0 = f"{self.input.get_struct_meta_ptr()} {self.input.get_struct_meta_name()}_init" \
               f"({self.input.get_struct_meta_ptr()}{meta_param_name}) {{\n" + \
               f"if (!{meta_param_name}) {meta_param_name}= {self.input.get_struct_meta_name()}_new();\n" + \
               f"{meta_param_name}->super.meta_list=mnarray_init_fill_with_0(0," \
               f"{self.input.get_lbl_fields_count()});\n" + \
               f"{meta_param_name}->super.table_name =\"{self.input.table_name}\";\n" + \
               "".join([f"{meta_param_name}->{d[lbl_name]}= "
                        f"mnmetadata_list_set_item_at({meta_param_name}->super.meta_list,"
                        f"\nmnmetadata_init(0,str_cpy(\"{d[lbl_name]}\"),"
                        f"{d[lbl_type]},{d[lbl_must_not_nul]},"
                        f"{d[lbl_is_unique]},\n{d[lbl_is_primary_key]},"
                        f"{d[lbl_is_auto_inc]},{d[lbl_default_val]}),"
                        f"{d[lbl_name].capitalize()});\n" for d in self.input.fields]) + \
               f"return {meta_param_name};\n}}\n"

        return str0

    def tbluser_meta_free(self):
        str0 = f"{void_name} {self.input.get_struct_meta_name()}_free({self.input.get_struct_meta_ptr_hld()}" \
               f" {meta_param_name}_hld){{\n" \
               f"mnarray_free(&((*{meta_param_name}_hld)->super.meta_list));\n" \
               f"mnfree(*{meta_param_name}_hld);\n" \
               f"*{meta_param_name}_hld=0;\n" \
               f"}}\n"
        return str0

    def tbluser_meta_clean_free(self):
        str0 = f"{void_name} {self.input.get_struct_meta_name()}_clean_free({self.input.get_struct_meta_ptr_hld()}" \
               f" {meta_param_name}_hld){{\n" \
               f" {self.input.get_struct_meta_name()}_clean(*{meta_param_name}_hld);\n" \
               f" {self.input.get_struct_meta_name()}_free({meta_param_name}_hld);\n" \
               f"}};\n"

        return str0

    def tbluser_meta_clean(self):
        str0 = f"{self.input.get_struct_meta_ptr()} {self.input.get_struct_meta_name()}_clean" \
               f"({self.input.get_struct_meta_ptr()} {meta_param_name}){{\n" \
               f"mnmetadata_list_clean({meta_param_name}->super.meta_list);\n" + \
               "".join([f"{meta_param_name}->{d[lbl_name]}=0;\n" for d in self.input.fields]) + \
               f"return {meta_param_name};\n" \
               f"}}\n"
        return str0

    def tbluser_record_init(self):
        str0 = f"{self.input.get_struct_record_ptr()} {self.input.get_struct_record_name()}_init" \
               f"({self.input.get_struct_record_ptr()} {record_param_name}," + \
               f",".join([f"mnvariant* {d[lbl_name]}\n" for d in self.input.fields]) + f") {{\n" + \
               f"if (!{record_param_name}) {record_param_name}= {self.input.get_struct_record_name()}_new();\n" \
               f"mnarray_init_fill_with_0(&{record_param_name}->" \
               f"super.var_list,{self.input.get_lbl_fields_count()});\n" + \
               "".join([f"{record_param_name}->{d[lbl_name]}={d[lbl_name]};"
                        f"\nmnvariantList_set_item_at(&{record_param_name}->super.var_list,"
                        f"{record_param_name}->{d[lbl_name]},{d[lbl_name].capitalize()});"
                        f"\n" for d in self.input.fields]) + \
               f"return {record_param_name};\n" \
               f"}}\n"

        return str0

    def tbluser_record_refresh_list(self):
        str0 = f"{void_name} {self.input.get_struct_record_name()}_refresh_list({void_name} *{record_param_name}_){{\n" \
               f"{self.input.get_struct_record_ptr()} {record_param_name} =" \
               f" ({self.input.get_struct_record_ptr()}){record_param_name}_;\n" \
               f"mnvariantList_clean(&{record_param_name}->super.var_list);\n" + \
               "".join(
                   [f" mnvariantList_add(&{record_param_name}->super.var_list,{record_param_name}->{d[lbl_name]});\n"
                    for d in self.input.fields]) + \
               f"}}\n"
        return str0

    def tbluser_record_new(self):
        str0 = f"{self.input.get_struct_record_ptr()} {self.input.get_struct_record_name()}_new(){{\n" \
               f"{self.input.get_struct_record_ptr()} {record_param_name}=({self.input.get_struct_record_ptr()}) " \
               f"mnalloc(sizeof({self.input.get_struct_record_name()}));\n" \
               f"mnassert({record_param_name});\n" + \
               f"".join([f"{record_param_name}->{d[lbl_name]}=0;\n" for d in self.input.fields]) + \
               f"{record_param_name}->super.refresh_list={self.input.get_struct_record_name()}_refresh_list;" \
               f"{record_param_name}->super.var_list_set_field_at=" \
               f"{self.input.get_struct_record_name()}_list_set_field_at_clean_ex;\n" \
               f"return {record_param_name};\n" \
               f"}}\n"

        return str0

    def tbluser_record_clean(self):
        str0 = f"{self.input.get_struct_record_ptr()} {self.input.get_struct_record_name()}_clean(" \
               f"{self.input.get_struct_record_ptr()} {record_param_name}){{\n" \
               f"mnarray_clean(&{record_param_name}->super.var_list,(mnfree_fnc) mnvariant_clean_free);\n" + \
               f"".join([f"{record_param_name}->{d[lbl_name]}=0;\n" for d in self.input.fields]) + \
               f"return {record_param_name};\n" \
               f"}}\n"
        return str0

    def tbluser_record_free(self):
        str0 = f"{void_name} {self.input.get_struct_record_name()}_free({self.input.get_struct_record_ptr_hld()}" \
               f" {record_param_name}_hld){{\n" \
               f"mnfree(*{record_param_name}_hld);\n" \
               f"*{record_param_name}_hld=0;\n" \
               f"}}\n"
        return str0

    def setters_def(self):
        str0 = "".join([f"{void_name} {self.input.get_struct_record_name()}_set_{d[lbl_name]}"
                        f"({self.input.get_struct_record_ptr()} {record_param_name},"
                        f"mnvariant* {d[lbl_name]}){{\n"
                        f"mnvariant_clean_free(&{record_param_name}->{d[lbl_name]});\n"
                        f"{record_param_name}->{d[lbl_name]}={d[lbl_name]};\n"
                        f"{self.input.get_struct_record_name()}_refresh_list({record_param_name});\n"
                        f"}}\n" for d in self.input.fields])
        return str0

    def tbluser_record_list_set_field_at(self):
        str0 = f"mnvariant * {self.input.get_struct_record_name()}_list_set_field_at(" \
               f"{self.input.get_struct_record_ptr()} {record_param_name}," \
               f"mnvariant *field,tbl{self.input.table_name}_fields_index ind){{\n" \
               f"mnvariantList* list= &{record_param_name}->super.var_list;\n" \
               f"list->array[ind] = field;\n" \
               f"switch (ind) {{\n" + \
               f"".join([f"case {d[lbl_name].capitalize()}:\n"
                         f"    {record_param_name}->{d[lbl_name]} = field;\n"
                         f"    break;\n" for d in self.input.fields]) + \
               f"default:\n" \
               f"mnassert(0);\n" \
               f"}}\n" \
               f"return field;\n" \
               f"}}\n"

        return str0

    def tbluser_record_list_set_field_at_clean_ex(self):
        str0 = f"mnvariant * {self.input.get_struct_record_name()}_list_set_field_at_clean_ex(" \
               f"{void_name} *{record_param_name}_,mnvariant *field,char ind){{\n" \
               f"{self.input.get_struct_record_ptr()} {record_param_name} = {record_param_name}_;\n" \
               f"mnvariantList* list= &{record_param_name}->super.var_list;\n" \
               f"if (list->array[ind]) mnvariant_clean_free((mnvariant **) &list->array[ind]);\n" \
               f"list->array[ind] = field;\n" \
               f"switch (ind) {{\n" + \
               f"".join([f"case {d[lbl_name].capitalize()}:\n"
                         f"    {record_param_name}->{d[lbl_name]} = field;\n"
                         f"    break;\n" for d in self.input.fields]) + \
               f"default:\n" \
               f"mnassert(0);\n" \
               f"}}\n" \
               f"return field;\n" \
               f"}}\n"

        return str0

    def source_file(self):
        str0 = self.source_intro() + self.source_includes() + \
               self.tbluser_meta_new() + self.tbluser_meta_init() + \
               self.tbluser_meta_free() + self.tbluser_meta_clean_free() + \
               self.tbluser_meta_clean() + self.tbluser_record_init() + \
               self.tbluser_record_refresh_list() + self.tbluser_record_new() + \
               self.tbluser_record_clean() + self.tbluser_record_free() + \
               self.setters_def() + self.tbluser_record_list_set_field_at_clean_ex() + \
               self.tbluser_record_list_set_field_at()
        return str0
