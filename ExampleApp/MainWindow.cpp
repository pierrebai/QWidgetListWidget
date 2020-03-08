#include "MainWindow.h"
#include "ExampleListItem.h"

namespace ExampleApp
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
      _list = new QWidgetListWidget;
      _list->setAcceptDrops(true);
      _scrollList = new QWidgetScrollListWidget(_list);

      setCentralWidget(_scrollList);
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
         _list->addItem(new ExampleListItem(QString::asprintf("Item #%d", i+1)));
   }
}
