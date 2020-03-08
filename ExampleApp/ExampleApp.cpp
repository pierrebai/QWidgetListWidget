#include "MainWindow.h"

#include <QtWidgets/qapplication.h>

static HINSTANCE appInstance;

namespace ExampleApp
{
   int App(int argc, char** argv)
   {
      QScopedPointer<QApplication> app(new QApplication(argc, argv));

      auto mainWindow = new MainWindow;

      mainWindow->resize(1000, 800);
      mainWindow->show();

      return app->exec();
   }
}

int main(int argc, char** argv)
{
   return ExampleApp::App(argc, argv);
}

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wchar_t* lpCmdLine, int nCmdShow)
{
   appInstance = hInstance;
   return main(0, 0);
}

