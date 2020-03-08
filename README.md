# QWidgetListWidget
Example of a Qt list  widget containing complex sub-widgets.

# Purpose
The QWidgetListWidget class is a list widget that can contain a list of arbitrary widgets as items.
The items can have any control put into them. The list widget supports scrolling, selection and drag-and-drop.

An example app showing how to use the list widget is included.

# Dependencies and Build 
The project requires Qt. It was built using Qt 5.12. It uses CMake to build the project. CMake 3.16.4 was used.

A script to generate a Visual-Studio solution is provided. In order for CMake to find Qt,
the environment variable QT5_DIR must be defined and must point to the Qt 5.12 directory.
For example:

        QT5_DIR=C:\Outils\Qt\5.12.1\

Alternatively, to invoke cmake directly, it needs to be told where to find Qt.
It needs the environment variable CMAKE_PREFIX_PATH set to the location of Qt.
For example:

        CMAKE_PREFIX_PATH=%QT5_DIR%\msvc2017_64

