add_library(mndb
    mnsql.h
    mnsql.c
    mnsqlite.h
    mnsqlite.c
    mndatabase.h
    mndatabase.c
        mntable.h
        mntable.c
        mnmetadata.h
        mnmetadata.c
        mnrecord.h mnrecord.c
        sqlite3.c
        sqlite3.h
        mn_db_const.h
        mnfilter.h
        mnfilter.c
        mndataset.c
        mndataset.h)
target_include_directories(mndb PUBLIC ./)
target_link_libraries(mndb  mnlibrary )
#target_include_directories(mnlibrary_test PUBLIC ../../mnlibrary)
#add_subdirectory(./mysql_conn/)

