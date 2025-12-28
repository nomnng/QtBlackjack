cmake_minimum_required(VERSION 3.5)

project(QtBlackjack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        widgets/main_window.cpp
        widgets/main_window.h
        widgets/card_widget.cpp
        widgets/card_widget.h
        widgets/control_buttons_widget.h
        widgets/control_buttons_widget.cpp
        widgets/game_widget.h
        widgets/game_widget.cpp
        widgets/popup_widget.h
        widgets/popup_widget.cpp
        widgets/bet_selection_popup.h
        widgets/bet_selection_popup.cpp
        game/card.h
        game/card.cpp
        game/blackjack.h
        game/blackjack.cpp
        utils/card_image_provider.h
        utils/card_image_provider.cpp
        assets.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtBlackjack
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtBlackjack APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtBlackjack SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtBlackjack
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(QtBlackjack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(QtBlackjack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/widgets)
#target_include_directories(QtBlackjack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/game)
#target_include_directories(QtBlackjack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/utils)

target_link_libraries(QtBlackjack PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QtBlackjack PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtBlackjack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtBlackjack)
endif()
