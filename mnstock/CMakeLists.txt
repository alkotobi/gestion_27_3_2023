cmake_minimum_required(VERSION 3.5)
project(mnstock VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.c
        modals/tblmodal.c modals/tblmodal.h)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(mnstock ${PROJECT_SOURCES})

target_link_libraries(mnstock PRIVATE Qt${QT_VERSION_MAJOR}::Widgets mnlibrary mndb cqt tbls ui)

set_target_properties(mnstock PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
add_subdirectory(./tbls)
add_subdirectory(./ui)
add_subdirectory(./tests)

