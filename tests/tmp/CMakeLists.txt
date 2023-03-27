cmake_minimum_required(VERSION 3.5)
project(tmp_t VERSION 0.1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SOURCES
        main.c
)
add_executable(tmp_t ${PROJECT_SOURCES})
target_link_libraries(tmp_t  mnlibrary )
target_link_libraries(tmp_t mndb)
target_include_directories(tmp_t PUBLIC ../../mndb)
target_include_directories(tmp_t PUBLIC ../../mnlibrary)
