add_library(tbls
        tbluser/tblusers.h
        tbluser/tblusers.c
        tblgroup/tblgroup.h
        tblgroup/tblgroup.c)
target_include_directories(tbls PUBLIC ./ ./tbluser)
target_link_libraries(tbls  mnlibrary )
target_link_libraries(tbls  mndb )