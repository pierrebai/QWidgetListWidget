from PySide2.QtWidgets import QLabel,QLineEdit,QCheckBox,QPushButton,QSizePolicy,QWidget,QHBoxLayout,QVBoxLayout,QLayout
from PySide2.QtGui import QPaintEvent,QPen,QColor,QPainter
from PySide2.QtCore import QSize
import qWidgetListItem

###
# A simple widget that draws diagonal lines to represent an area
# the user can grab to drag-and-drop.
# Ensures there is at least this area that can be grabbed in the
# ExampleListItem.
###
class Grabber(QWidget):
    def __init__(self):
        super().__init__()
    def paintEvent(self,event : QPaintEvent):
        pen = QPen(QColor(180,180,180,128))
        pen.setWidth(3)

        h = self.height()
        w = self.width()

        painter = QPainter(self)
        painter.setPen(pen)
        offset = 4
        diagonal = 10
        for y in range(offset,h - (offset+diagonal),diagonal):
            painter.drawLine(0 , y, w, y+diagonal)

class ListItem(qWidgetListItem.QWidgetListItem):
    def __init__(self,text = '', is_checked = False):
        super().__init__()
        self.init_text = text
        self.init_is_checked = is_checked
        self.setToolTip('example item')
        self.setSizePolicy(QSizePolicy.Minimum,QSizePolicy.Minimum)

        # Horizontal Layout to contain the Grabber and the rest of the Gui
        top_layout = QHBoxLayout(self)
        top_layout.setMargin(0)
        self.setLayout(top_layout)

        # Grabber to always give some area to grab for drag-and-drop.
        handle = self.create_grabber()
        top_layout.addWidget(handle)

        # Layouts for the UI
        container_layout,name_layout=self.create_layouts()

        #The UI
        name_label = QLabel('Label')
        name_layout.addWidget(name_label)

        text_edit = QLineEdit(text)
        name_layout.addWidget(text_edit)

        edit_button = QPushButton('Button')
        name_layout.addWidget(edit_button)

        include_box = QCheckBox('Check')
        include_box.setChecked(is_checked)
        container_layout.addWidget(include_box)
        top_layout.addLayout(container_layout)

        # Add this when adding to a horizontal list.
        # container_layout.addStretch(0);

    def create_grabber(self):
        handle = Grabber()
        handle.setSizePolicy(QSizePolicy(QSizePolicy.Policy.Fixed,QSizePolicy.Policy.Preferred))
        handle.setMinimumSize(QSize(8,8))
        return handle

    def create_layouts(self):
        container_layout = QVBoxLayout()
        container_layout.setSizeConstraint(QLayout.SetMinAndMaxSize)
        container_layout.setMargin(4)

        name_layout = QHBoxLayout()
        name_layout.setSizeConstraint(QLayout.SetMinAndMaxSize)
        name_layout.setMargin(0)
        container_layout.addLayout(name_layout)

        return container_layout,name_layout

    def clone(self):
        return ListItem( text = self.init_text, is_checked = self.init_is_checked )

