cmake_minimum_required(VERSION 3.5)
project(cqt_test VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.c
        testing.h
        testing.c
        cqdir_t.h
        cqdir_t.c
        cqStandardPaths_t.h
        cqStandardPaths_t.c)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(cqt_test ${PROJECT_SOURCES})

target_link_libraries(cqt_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets mnlibrary cqt)

set_target_properties(cqt_test PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)


