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
      BuildUI();
      FillUI();
      ConnectUI();
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the UI elements.

   void MainWindow::BuildUI()
   {
      _list = new QWidgetListWidget;
      _list->setAcceptDrops(true);
      _scrollList = new QWidgetScrollListWidget(_list);

      setCentralWidget(_scrollList);
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Connect the signals of the UI elements.

   void MainWindow::ConnectUI()
   {
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Fill the UI with the intial data.

   void MainWindow::FillUI()
   {
      for (int i = 0; i < 10; ++i)
         _list->AddItem(new ExampleListItem(QString::asprintf("Item #%d", i+1)));
   }
}
