# Open a new file named "example.txt" in write mode
from header import *
from source import *




with open(header, "w") as file:
    # Write some text to the file
    file.write(intro() + includes() + \
               consts()+\
               struct_meta() + \
               struct_meta_methods() + \
               struct_record() + \
               struct_record_methods()+setters())

with open(source, "w") as file:
    # Write some text to the file
    file.write(source_intro()+source_includes() +
               tbluser_meta_new()+tbluser_meta_init()+
               tbluser_meta_free()+tbluser_meta_clean_free()+
               tbluser_meta_clean()+tbluser_record_init()+
               tbluser_record_refresh_list()+tbluser_record_new()+
               tbluser_record_clean()+tbluser_record_free()+
               setters_def()+tbluser_record_list_set_field_at_clean_ex()+
               tbluser_record_list_set_field_at())
    # Confirm that the file was created and written to by reading its contents
import shutil
import os

# Copy the contents of tblgroup.h to a temporary file
shutil.copyfile('tblgroup.h', 'tblgroup_tmp.txt')

# Read the contents of the temporary file
try:
    with open('tblgroup_tmp.txt', 'r', encoding='utf-8') as file:
        contents = file.read()
        if contents:
            print(contents)
        else:
            print("File is empty.")
except Exception as e:
    print(f"Error reading file: {e}")

# Delete the temporary file
try:
    os.remove('tblgroup_tmp.txt')
    print("File deleted successfully.")
except Exception as e:
    print(f"Error deleting file: {e}")
