from listItem import ListItem
from PySide2.QtWidgets import QHBoxLayout,QWidget, QMainWindow,QBoxLayout
from qWidgetListItem import QWidgetListItem
from qWidgetListWidget import QWidgetListWidget
from qWidgetScrollListWidget import QWidgetScrollListWidget

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        scroll_list_1 = self.buildUI()
        self.fillUI(scroll_list_1.widget())
        self.connectUI()

    def build_scroll_list_widget(self, _dir = QBoxLayout.Direction.TopToBottom ):
        _list = QWidgetListWidget(stretch=True, _dir = _dir)
        #_list.setAcceptDrops(True)

        scroll_list = QWidgetScrollListWidget(_list)
        return scroll_list

    def buildUI(self):
        container = QWidget()
        layout = QHBoxLayout()

        scroll_list_1 = self.build_scroll_list_widget()
        scroll_list_2 = self.build_scroll_list_widget()

        layout.addWidget(scroll_list_1)
        layout.addWidget(scroll_list_2)

        container.setLayout(layout)
        self.setCentralWidget(container)

        return scroll_list_1

    def connectUI(self):
        pass

    def fillUI(self,_list):
        for i in range(10):
            _list.add_item(ListItem('Item {}'.format(i+1)))
