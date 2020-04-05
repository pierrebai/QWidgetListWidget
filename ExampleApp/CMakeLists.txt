# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)

add_executable(ExampleApp WIN32
   ExampleApp.cpp
   MainWindow.cpp          MainWindow.h
   ExampleListItem.cpp     ExampleListItem.h
)

target_link_libraries(ExampleApp PUBLIC
   QWidgetListWidget
   Qt5::Widgets Qt5::Gui Qt5::Core
)

target_compile_features(ExampleApp PUBLIC cxx_std_20)

target_include_directories(ExampleApp PUBLIC
   "${PROJECT_SOURCE_DIR}/QtAdditions/inc"
)

add_custom_command(TARGET ExampleApp POST_BUILD
   COMMAND "${Qt5_DIR}/../../../bin/windeployqt.exe" --no-webkit2 --no-angle --no-system-d3d-compiler --no-opengl-sw "$<TARGET_FILE:ExampleApp>"
)

