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

   /////////////////////////////////////////////////////////////////////////
   //
   // Main window of the example.
   //
   // Contains two list widgets that can exchange items via drag-and-drop.

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
      QWidgetListWidget* _list1 = nullptr;
      QWidgetScrollListWidget* _scrollList1 = nullptr;

      QWidgetListWidget* _list2 = nullptr;
      QWidgetScrollListWidget* _scrollList2 = nullptr;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
