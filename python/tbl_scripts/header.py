from const import *


def includes():
    str0 = "#include \"mnsql.h\"\n" + \
           "#include \"mnmetadata.h\"\n"
    return str0


def struct_meta():
    str1 = "typedef struct {\n" + \
           "    tbl_super super;\n" + \
           '\n'.join(["    mnmetadata* {};".format(d['name']) for d in fields]) + "\n}}{};\n".format(struct_meta_name)
    return str1


def struct_meta_methods():
    str1 = struct_meta_ptr + struct_meta_name + "_new();\n" + \
           struct_meta_ptr + struct_meta_name + "_init({} {});\n".format(struct_meta_ptr, meta_param_name) + \
           struct_meta_ptr + struct_meta_name + "_clean({} {});\n".format(struct_meta_ptr, meta_param_name) + \
           void_name + struct_meta_name + "_free({} {}_hld);\n".format(struct_meta_ptr_hld, meta_param_name) + \
           void_name + struct_meta_name + "_clean_free({} {}_hld);\n\n\n".format(struct_meta_ptr_hld, meta_param_name)
    return str1


def struct_record():
    str0 = "typedef struct {\n    mnvariantList var_list;\n" + \
           '\n'.join(["    mnvariant* {};".format(d['name']) for d in fields]) + \
           "\n}}{};\n".format(struct_record_name)
    return str0


def struct_record_methods():
    str0 = struct_record_ptr + struct_record_name + "_init(" + struct_record_ptr + record_param_name + ",{});\n". \
        format(',\n'.join(["    mnvariant* {}".format(d['name']) for d in fields])) + \
           struct_record_ptr + struct_record_name + "_refresh({} {});\n".format(struct_record_ptr, record_param_name) + \
           struct_record_ptr + struct_record_name + "_clean({} {});\n".format(struct_record_ptr, record_param_name) + \
           void_name + struct_record_name + "_free({} {}_hld);\n".format(struct_record_ptr_hld,
                                                                                 record_param_name)+\
            f"{struct_record_ptr} {struct_record_name}_new();\n"
    return str0
