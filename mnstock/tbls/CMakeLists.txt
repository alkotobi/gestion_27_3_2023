add_library(tbls
        tbluser/tbluser.h
        tbluser/tbluser.c
        tblgroup/tblgroup.h
        tblgroup/tblgroup.c
        )
target_include_directories(tbls PUBLIC ./ ./tbluser)
target_link_libraries(tbls  mnlibrary )
target_link_libraries(tbls  mndb )