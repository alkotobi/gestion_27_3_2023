from const import *


class Header:
    def __init__(self, user_input):
        self.inputs = user_input

    def consts(self):
        str0 = f"#define {self.inputs.get_lbl_fields_count()} {self.inputs.get_fields_count()}\n" + \
               f"typedef enum{{" + \
               ",".join([f"{d[lbl_name]}".capitalize() for d in self.inputs.fields]) + \
               f"}} tbl{self.inputs.table_name}_fields_index;\n"

        return str0

    @staticmethod
    def includes():
        str0 = "#include \"mnsql.h\"\n" + \
               "#include \"mnmetadata.h\"\n"
        return str0

    def struct_meta(self):
        str1 = "typedef struct {\n" + \
               "    tbl_super super;\n" + \
               '\n'.join(["    mnmetadata* {};".format(d['name']) for d in self.inputs.fields]) + \
               "\n}}{};\n".format(self.inputs.get_struct_meta_name())
        return str1

    def struct_meta_methods(self):
        str1 = self.inputs.get_struct_meta_ptr() + self.inputs.get_struct_meta_name() + "_new();\n" + \
               self.inputs.get_struct_meta_ptr() + self.inputs.get_struct_meta_name() + "_init({} {});\n".format(
            self.inputs.get_struct_meta_ptr(), meta_param_name) + \
               self.inputs.get_struct_meta_ptr() + self.inputs.get_struct_meta_name() + "_clean({} {});\n".format(
            self.inputs.get_struct_meta_ptr(), meta_param_name) + \
               void_name + self.inputs.get_struct_meta_name() + "_free({} {}_hld);\n".format(
            self.inputs.get_struct_meta_ptr_hld(), meta_param_name) + \
               void_name + self.inputs.get_struct_meta_name() + "_clean_free({} {}_hld);\n\n\n".format(
            self.inputs.get_struct_meta_ptr_hld(), meta_param_name)
        return str1

    # def struct_record_super():
    #     str0=f"typedef struct {{\n" \
    #          f"mnvariantList var_list;\n" \
    #          f"void(*refresh_list)(void*);\n" \
    #          f"}}record_super;\n"
    #     return str0
    def struct_record(self):
        str0 = "typedef struct {\n    //mnvariantList var_list;\n" \
               "record_super super;\n" + \
               '\n'.join(["    mnvariant* {};".format(d['name']) for d in self.inputs.fields]) + \
               "\n}}{};\n".format(self.inputs.get_struct_record_name())
        return str0

    def struct_record_methods(self):
        str0 = self.inputs.get_struct_record_ptr() + self.inputs.get_struct_record_name() + "_init(" + \
               self.inputs.get_struct_record_ptr() + record_param_name + \
               ",{});\n".format(',\n'.join(["    mnvariant* {}".format(d['name']) for d in self.inputs.fields])) + \
               f"{void_name}  {self.inputs.get_struct_record_name()}_refresh_list" + \
               "({} *{}_);\n".format(void_name, record_param_name) + \
               self.inputs.get_struct_record_ptr() + self.inputs.get_struct_record_name() + \
               "_clean({} {});\n".format(self.inputs.get_struct_record_ptr(), record_param_name) + \
               void_name + self.inputs.get_struct_record_name() + \
               "_free({} {}_hld);\n".format(self.inputs.get_struct_record_ptr_hld(), record_param_name) + \
               f"{self.inputs.get_struct_record_ptr()} {self.inputs.get_struct_record_name()}_new();\n" \
               f"mnvariant * {self.inputs.get_struct_record_name()}_list_set_field_at(" \
               f"{self.inputs.get_struct_record_ptr()} {record_param_name},mnvariant " \
               f"*field,tbl{self.inputs.table_name}_fields_index ind);\n" \
               f"mnvariant * {self.inputs.get_struct_record_name()}_list_set_field_at_clean_ex(" \
               f"{void_name} *{record_param_name}_,mnvariant *field,char ind);\n"
        return str0

    def setters(self):
        str0 = "".join([f"{void_name} {self.inputs.get_struct_record_name()}_set_{d[lbl_name]}"
                        f"({self.inputs.get_struct_record_ptr()} {record_param_name},"
                        f"mnvariant* {d[lbl_name]});\n" for d in self.inputs.fields])
        return str0

    def header_file(self):
        str0 = intro() + self.includes() + \
               self.consts() + \
               self.struct_meta() + \
               self.struct_meta_methods() + \
               self.struct_record() + \
               self.struct_record_methods() + self.setters()
        return str0
