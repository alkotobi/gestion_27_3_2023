cmake_minimum_required(VERSION 3.5)
project(mnlibrary_test VERSION 0.1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SOURCES
        main.c
        mnarray_t.h
        mnarray_t.c
        cstring_test.h
        cstring_test.c
        mnvariant_t.h
        mnvariant_t.c
        mncstringList_t.h
        mncstringList_t.c
        mnstring_t.h
        mnstring_t.c
        mndictionary_t.h mndictionary_t.c)
add_executable(mnlibrary_test ${PROJECT_SOURCES})
target_link_libraries(mnlibrary_test  mnlibrary )
target_include_directories(mnlibrary_test PUBLIC ../../mnlibrary)