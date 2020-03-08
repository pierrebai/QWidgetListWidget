# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)

add_library(QtAdditions
   QWidgetListItem.cpp           QWidgetListItem.h
   QWidgetScrollListWidget.cpp   QWidgetScrollListWidget.h
   QWidgetListWidget.cpp         QWidgetListWidget.h
   QWidgetListMimeData.h
)

target_compile_features(QtAdditions PUBLIC cxx_std_20)

target_include_directories(QtAdditions PUBLIC
   "${Qt5Core_INCLUDE_DIRS}"
   "${Qt5Widgets_INCLUDE_DIRS}"
   "${Qt5Gui_INCLUDE_DIRS}"
)

