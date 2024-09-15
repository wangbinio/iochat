cmake_minimum_required(VERSION 3.25)

project(iochat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/msvc2019_64")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("E:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        logindialog.h
        logindialog.cpp
        logindialog.ui
        registerdialog.h
        registerdialog.cpp
        registerdialog.ui
        global.h
        global.cpp
        singleton.h
        httpmgr.h
        httpmgr.cpp
        qtimerbutton.cpp
        qtimerbutton.h
        clicked_label.cpp
        clicked_label.h
        resetdialog.cpp
        resetdialog.h
        resetdialog.ui
)

add_executable(iochat
        ${PROJECT_SOURCES}
        ${app_icon_resource_windows}
        rc.qrc

)

target_link_libraries(iochat PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
        fmt::fmt
        nlohmann_json::nlohmann_json
        unofficial-sodium::sodium
)

add_custom_command(TARGET iochat POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}
        COMMENT "Copying config.ini to executable directory"
)
