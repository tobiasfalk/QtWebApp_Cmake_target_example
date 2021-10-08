# SPDX-License-Identifier: LGPL-3.0
# Setup
option(QTWEBAPP_DOWNLOAD_NEWEST "If on downloads the newset version from the web" OFF)
set(QTWEBAPP_ARCHIVE_VERSION "1-8-3" CACHE STRING "Sets the QtWebApp Version, the version number is spaced with an -")

# Download or get from archive and Extract the Src
if(${QTWEBAPP_DOWNLOAD_NEWEST})
    # Downloads from web
    message(STATUS "QtWebApp: Download the newest version from web")
    file(DOWNLOAD http://stefanfrings.de/qtwebapp/QtWebApp.zip ${CMAKE_BINARY_DIR}/QtWebApp.zip)
else()
    # Use archive Version
    message(STATUS "QtWebApp: use archive version: ${QTWEBAPP_ARCHIVE_VERSION}")
    file(COPY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Archive/QtWebApp-${QTWEBAPP_ARCHIVE_VERSION}.zip ${CMAKE_BINARY_DIR}/QtWebApp.zip)
endif()

file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/QtWebApp.zip)

# Setup End

#
# QtWebApp Doc and Wrapper
#

# Edit doc main page to not make Problems for main Projekt
FILE(READ ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/doc/mainpage.dox DOC_FILE_IN)
STRING(REGEX REPLACE "@mainpage" "" DOC_FILE_OUT "${DOC_FILE_IN}" )
STRING(REPLACE "/**" "" DOC_FILE_OUT "${DOC_FILE_OUT}" )
STRING(REPLACE "*/" "" DOC_FILE_OUT "${DOC_FILE_OUT}" )
FILE(WRITE ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/doc/mainpage.dox "${DOC_FILE_OUT}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/QtWebApp_README.in.md ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/QtWebApp_README.md)
FILE(READ ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/QtWebApp_README.md QtWebApp_Doc_In)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/QtWebApp.in.h ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/QtWebApp.h)


add_custom_target(QtWebApp ALL
    SOURCES
        QtWebApp.in.h
        QtWebApp_README.in.md
)
add_dependencies(QtWebApp QtWebApp_Httpserver QtWebApp_Logging QtWebApp_Templateengine)

# QtWebApp Doc and Wrapper End

#
# Httpserver
#

# Find needed Packeges
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

# Find all Src files, .cpp and .f
file(GLOB QtWebApp_Httpserver_SRC
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/httpserver/*.h"
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/httpserver/*.cpp"
)

# Find all headers, .h
file(GLOB QtWebApp_Httpserver_SRC_headers
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/httpserver/*.h"
)

# Create lib
add_library(QtWebApp_Httpserver SHARED ${QtWebApp_Httpserver_SRC})

# Ling needed libs
target_link_libraries(QtWebApp_Httpserver PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

# Ad header location
target_include_directories(QtWebApp_Httpserver PUBLIC ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/httpserver/)

# Httpserver End


#
# Logging
#

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# Find all Src files, .cpp and .f
file(GLOB QtWebApp_Logging_SRC
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/logging/*.h"
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/logging/*.cpp"
)

# Find all headers, .h
file(GLOB QtWebApp_Logging_SRC_headers
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/logging/*.h"
)

# Create lib
add_library(QtWebApp_Logging SHARED ${QtWebApp_Logging_SRC})

# Ling needed libs
target_link_libraries(QtWebApp_Logging PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

# Ad header location
target_include_directories(QtWebApp_Logging PUBLIC ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/logging/)

# Logging End


#
# Templateengine
#

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

if(${QT_VERSION_MAJOR} EQUAL 6)

    find_package(Qt6 COMPONENTS Core5Compat REQUIRED)

endif()

# Find all Src files, .cpp and .f
file(GLOB QtWebApp_Templateengine_SRC
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/templateengine/*.h"
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/templateengine/*.cpp"
)

# Find all headers, .h
file(GLOB QtWebApp_Templateengine_SRC_headers
     "${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/templateengine/*.h"
)

# Replace Qt6 needed headers
if(${QT_VERSION_MAJOR} EQUAL 6)

    foreach(FILE IN LISTS QtWebApp_Templateengine_SRC_headers)
        FILE(READ ${FILE} FILE_IN)
        STRING(REGEX REPLACE "#include <QTextCodec>" "#include <QtCore5Compat/QTextCodec>" FILE_OUT "${FILE_IN}" )
        FILE(WRITE ${FILE} "${FILE_OUT}")
    endforeach()

endif()

# Create lib
add_library(QtWebApp_Templateengine SHARED ${QtWebApp_Templateengine_SRC})

# Ling needed libs
target_link_libraries(QtWebApp_Templateengine PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
if(${QT_VERSION_MAJOR} EQUAL 6)

    target_link_libraries(QtWebApp_Templateengine PUBLIC Qt6::Core5Compat)

endif()

# Ad header location
target_include_directories(QtWebApp_Templateengine PUBLIC ${CMAKE_BINARY_DIR}/QtWebApp/QtWebApp/QtWebApp/templateengine/)

# Templateengine End
