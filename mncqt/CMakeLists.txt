cmake_minimum_required(VERSION 3.14)
set(CMAKE_PREFIX_PATH "~/dev/qt-everywhere-src-6.1.1/BUILD-STATIC/lib/cmake/")
project(cqt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(cqt STATIC
cqheader.h
cqheader.cpp
cqstring.h
cqstring.cpp
cqvariant.h
cqvariant.cpp
cqwidget.h
cqwidget.cpp
cqlayout.h
cqlayout.cpp
cqapplication.h
cqapplication.cpp
cqlabel.h
cqlabel.cpp
cqpushButton.h
cqpushButton.cpp
cqdebug.h
cqdebug.cpp
cqlineEdit.h
cqlineEdit.cpp
cqtableview.h
cqtableview.cpp
        mnsql_modal.h
        mnsql_modal.cpp
        QSqlModal.h
        QSqlModal.cpp
cpp.h
cpp.cpp
cqdir.h
cqdir.cpp
cqStandardPaths.h
cqStandardPaths.cpp
        qt_const.h)

target_link_libraries(cqt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets mnlibrary)
target_compile_definitions(cqt PRIVATE CQT_LIBRARY)
target_include_directories(cqt PUBLIC ./)
