#pragma once

#ifndef EXAMPLE_APP_MAIN_WINDOW_H
#define EXAMPLE_APP_MAIN_WINDOW_H

#include "QWidgetScrollListWidget.h"
#include "QWidgetListWidget.h"

#include <QtWidgets/qmainwindow.h>

namespace ExampleApp
{
   using QWidgetScrollListWidget = QtAdditions::QWidgetScrollListWidget;
   using QWidgetListWidget = QtAdditions::QWidgetListWidget;

   class MainWindow : public QMainWindow
   {
   public:
      // Create the main window.
      MainWindow();

   protected:
      // Create the UI elements.
      void buildUI();

      // Connect the signals of the UI elements.
      void connectUI();

      // Fill the UI with the intial data.
      void fillUI();

      // UI elements.
      QWidgetListWidget* _list = nullptr;
      QWidgetScrollListWidget* _scrollList = nullptr;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
