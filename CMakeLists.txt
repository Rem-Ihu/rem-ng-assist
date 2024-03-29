cmake_minimum_required(VERSION 3.5)

project(REM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Svg)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Quick3D Widgets)
#find_package(Qt6 REQUIRED WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)
find_package(Qt6 REQUIRED Multimedia)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        icons.qrc
        chart_data.qrc
        databasehandler1.h
        colors.qss
        main.qss
        includes.h
        login_sign_up_in.h
        login_sign_up_in.cpp
        login_sign_up_in.ui
        global_variables.h
        font.qrc
        firebaseget.h
        firebaseget.cpp
        secdialog.ui
        secdialog.cpp
        secdialog.h
        3d.qml
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(REM
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET REM APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(REM SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(REM
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(REM PRIVATE Qt${QT_VERSION_MAJOR}::Svg)
target_link_libraries(REM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(REM PRIVATE Qt${QT_VERSION_MAJOR}::Charts)
target_link_libraries(REM PRIVATE Qt${QT_VERSION_MAJOR}::Network)
#target_link_libraries(REM PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
target_link_libraries(REM  PRIVATE Qt::WebEngineWidgets)
target_link_libraries(REM PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)


target_link_libraries(REM PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Quick3D
)

set_target_properties(REM PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(REM)
endif()
