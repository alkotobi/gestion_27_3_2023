add_library(mnlibrary
  mntest.h
  mntest.c
  mnsystem.h
  mnsystem.c
  mnarray.h
  mnarray.c
  mnstring.c
  mnstring.h
  mncstring.h
  mncstring.c
  mncstringList.c
  mncstringList.h
  mnvariant.h
  mnvariant.c
  mnvariantList.h
  mnvariantList.c
        ../mndb/mnmetadata.h ../mndb/mnmetadata.c mndictionary.h mndictionary.c mnarray_char.h mnarray_char.c)
target_include_directories(mnlibrary PUBLIC ./)
