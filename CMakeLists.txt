# SPDX-License-Identifier: LGPL-3.0
cmake_minimum_required(VERSION 3.14)
project(QtWebApp_Cmake_target_example LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# this is how you integrate the QtWebApp in to your Projekt
subdirs(QtWebApp)


add_executable(QtWebApp_Cmake_target_example
  main.cpp
  README.md
  LICENSE.txt
)
target_link_libraries(QtWebApp_Cmake_target_example PUBLIC Qt${QT_VERSION_MAJOR}::Core QtWebApp_Httpserver QtWebApp_Logging QtWebApp_Templateengine)
