from PySide2.QtWidgets import QScrollArea,QWidget,QSizePolicy
from PySide2.QtCore import Qt


class QWidgetScrollListWidget(QScrollArea):
    def __init__(self,widget : QWidget, parent : QWidget = None):
        super().__init__(parent)
        self.setWidget(widget)
        self.isVertical = widget.isVertical()

        if self.isVertical:
            self.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
            self.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
            self.setSizePolicy(QSizePolicy.Minimum,QSizePolicy.MinimumExpanding)
        else:
            self.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
            self.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
            self.setSizePolicy(QSizePolicy.MinimumExpanding,QSizePolicy.Minimum)

        self.setWidgetResizable(True)
        self.setSizeAdjustPolicy(self.sizeAdjustPolicy().AdjustToContents)
