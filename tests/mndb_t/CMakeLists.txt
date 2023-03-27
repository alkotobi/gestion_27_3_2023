cmake_minimum_required(VERSION 3.5)
project(mndb_test VERSION 0.1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SOURCES
        main.c
        mnsql_t.h
        mnsql_t.c
        mnsqlite_t.h
        mnsqlite_t.c
        mntable_t.h mntable_t.c mnfilter_t.c mnfilter_t.h mndataset_t.c mndataset_t.h)
add_executable(mndb_test ${PROJECT_SOURCES})
target_link_libraries(mndb_test  mndb )
target_link_libraries(mndb_test tbls)
target_include_directories(mndb_test PUBLIC ../../mndb)