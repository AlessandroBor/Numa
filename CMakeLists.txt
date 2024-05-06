cmake_minimum_required(VERSION 3.5)
project(Numa VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/YOURUSERNAME/Qt/6.7.0/macos/lib/cmake") #Modify this path to your local QT installation's cmake directory.

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)


set(PROJECT_SOURCES
    src/mainwindow.cpp
    src/mainwindow.ui
    Resources/icons.qrc
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/Resources/ DESTINATION ${CMAKE_BINARY_DIR}/images/)

set(MACOSX_BUNDLE_ICON_FILE "Numa.icns")
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Numa.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


qt_add_executable(Numa MACOSX_BUNDLE ${app_icon_macos}
    src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui src/main.cpp Resources/Numa.png Resources/Numa.icns Resources/colorWheelIcon.svg Resources/underline-icon.svg  Resources/textcolor-icon.svg Resources/highlight-icon.svg Resources/italic-icon.svg Resources/bold-icon.svg Resources/open-icon.svg Resources/open.svg Resources/icons.qrc)

target_link_libraries(Numa PRIVATE Qt6::Widgets Qt6::Core)

set_target_properties(Numa PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Numa)
endif()

install(TARGETS Numa
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
