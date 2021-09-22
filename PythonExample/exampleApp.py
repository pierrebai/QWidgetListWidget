from PySide2.QtWidgets import QApplication
from mainWindow import MainWindow
import sys

def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    #main_window.resize(1000,800)
    main_window.show()
    return app.exec_()
    

if __name__ == '__main__':
    sys.exit(main())
    
