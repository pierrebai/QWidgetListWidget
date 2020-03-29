#include "MainWindow.h"
#include "ExampleListItem.h"

#include <QtWidgets/qboxlayout.h>

namespace dak::ExampleApp
{
   using namespace QtAdditions;
   using namespace std;

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the main window.

   MainWindow::MainWindow()
   {
      buildUI();
      fillUI();
      connectUI();
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the UI elements.

   void MainWindow::buildUI()
   {
      auto container = new QWidget;
      auto layout = new QHBoxLayout;
      container->setLayout(layout);

      _list1 = new QWidgetListWidget(nullptr, true, QBoxLayout::Direction::TopToBottom);
      //_list1 = new QWidgetListWidget(nullptr, true, QBoxLayout::Direction::LeftToRight);
      _list1->setAcceptDrops(true);
      _scrollList1 = new QWidgetScrollListWidget(_list1);
      layout->addWidget(_scrollList1);

      _list2 = new QWidgetListWidget(nullptr, true, QBoxLayout::Direction::TopToBottom);
      //_list2 = new QWidgetListWidget(nullptr, true, QBoxLayout::Direction::LeftToRight);
      _list2->setAcceptDrops(true);
      _scrollList2 = new QWidgetScrollListWidget(_list2);
      layout->addWidget(_scrollList2);

      setCentralWidget(container);
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Connect the signals of the UI elements.

   void MainWindow::connectUI()
   {
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Fill the UI with the intial data.

   void MainWindow::fillUI()
   {
      for (int i = 0; i < 10; ++i)
         _list1->addItem(new ExampleListItem(QString::asprintf("Item #%d", i+1)));
   }
}
