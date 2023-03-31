from datetime import datetime

today = datetime.today()


def intro():
    str1 = "//\n" + \
           "// Created by merhab on {today}.\n" + \
           "//\n""" + "#pragma once\n"
    return str1


struct_name = input("what is your struct name?\n")
param = struct_name[2:len(struct_name) + 1]


def header():
    str0 = f"{intro()}\n\n\n" \
           f"#include \"mnsystem.h\"\n\n" \
           f"typedef struct {{\n\n\n}} {struct_name};\n" \
           f"{struct_name}* {struct_name}_new();\n" \
           f"{struct_name}* {struct_name}_init({struct_name}* {param});\n" \
           f"{struct_name}* {struct_name}_clean({struct_name}* {param});\n" \
           f"void {struct_name}_free({struct_name}** {param}_hld);\n" \
           f"void {struct_name}_clean_free({struct_name}** {param}_hld);\n"
    return str0


def source():
    str0 = f"{intro()}\n\n\n" \
           f"#include \"{struct_name}.h\"\n\n\n" \
           f"{struct_name}* {struct_name}_new()" \
           f"{{\n" \
           f"     {struct_name} *{param}=({struct_name}*) mnalloc(sizeof({struct_name}));\n" \
           f"     mnassert({param});\n\n\n" \
           f"     //ur code here\n\n" \
           f"     return {param};\n" \
           f"}}\n" \
           f"{struct_name}* {struct_name}_init({struct_name}* {param}){{\n return {param};\n}}\n" \
           f"{struct_name}* {struct_name}_clean({struct_name}* {param}){{\n return {param};\n}}\n" \
           f"void {struct_name}_free({struct_name}** {param}_hld)" \
           f"{{\n" \
           f"     mnfree(*{param}_hld);\n" \
           f"     *{param}_hld=0;\n" \
           f"}}\n" \
           f"void {struct_name}_clean_free({struct_name}** {param}_hld)" \
           f"{{\n" \
           f"     {struct_name}_clean(*{param}_hld);\n" \
           f"     {struct_name}_free({param}_hld);\n" \
           f"}}\n"
    return str0


with open(f'{struct_name}.h', 'w', encoding='utf-8') as file:
    file.write(header())

with open(f'{struct_name}.c', 'w', encoding='utf-8') as file:
    file.write(source())
