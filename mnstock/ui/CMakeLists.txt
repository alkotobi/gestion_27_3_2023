cmake_minimum_required(VERSION 3.14)
set(CMAKE_PREFIX_PATH "~/dev/qt-everywhere-src-6.1.1/BUILD-STATIC/lib/cmake/")
project(ui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(ui STATIC
        ./login/frmlogincpp.h
        ./login/frmlogincpp.cpp
        ./login/frmlogin.h
        ./login/frmlogin.cpp
        )
target_include_directories(ui PUBLIC ./ ./login/)
target_link_libraries(ui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets mnlibrary mndb cqt)
target_compile_definitions(ui PRIVATE UI_LIBRARY)
