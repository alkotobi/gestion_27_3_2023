# Open a new file named "example.txt" in write mode
from header import *
from source import *

user_imput = User_Input()
header = Header(user_imput)
source = Source(user_imput)
user_imput.get_user_input()

with open(user_imput.get_header(), "w") as file:
    file.write(header.header_file())

with open(user_imput.get_source(), "w") as file:
    file.write(source.source_file())
