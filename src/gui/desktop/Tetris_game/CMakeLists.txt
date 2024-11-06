cmake_minimum_required(VERSION 3.5)

project(Tetris_QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

cmake_path(GET CMAKE_SOURCE_DIR PARENT_PATH TEMP_DIR)
cmake_path(GET TEMP_DIR PARENT_PATH TEMP_DIR)
cmake_path(GET TEMP_DIR PARENT_PATH THREE_LEVELS_UP)
add_compile_definitions("THREE_LEVELS_UP=${THREE_LEVELS_UP}")

set(PROJECT_SOURCES
        main.cpp
        tetriswindow.cpp
        tetriswindow.h
        tetriswindow.ui
        gamefield.h
        gamefield.cpp
        textfield.h
        textfield.cpp
        gameoverfield.h
        gameoverfield.cpp
        ../../../brick_game/tetris/functions/check.cc
        ../../../brick_game/tetris/functions/init.cc
        ../../../brick_game/tetris/functions/move.cc
        ../../../brick_game/tetris/functions/tools.cc
        ../../../brick_game/tetris/tetris.h
        resource/resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Tetris_QT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Tetris_QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Tetris_QT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Tetris_QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Tetris_QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Tetris_QT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Tetris_QT)
endif()
