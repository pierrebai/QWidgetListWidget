from PySide2.QtWidgets import QFrame,QBoxLayout,QWidget,QSizePolicy,QLayout,QLabel
from PySide2.QtGui import QPalette
from PySide2.QtCore import QSize
from qWidgetListItem import QWidgetListItem

class QWidgetListWidget(QFrame):
    def __init__(self,stretch = False, _dir = QBoxLayout.Direction.TopToBottom, parent : QWidget = None):
        super().__init__(parent)
        self.setBackgroundRole(QPalette.ColorRole.Base)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum))
        self.setMinimumSize(QSize(20, 20))
        if not stretch:
            setFrameStyle(QFrame.Box)

        _layout = QBoxLayout(_dir)
        _layout.setSizeConstraint(QLayout.SetMinimumSize)
        _layout.setMargin(2)
        _layout.setSpacing(0)
        self.setLayout(_layout)

        _dropHere = QLabel("Drop items here.")
        _dropHere.setForegroundRole(QPalette.ColorRole.Mid)
        _dropHere.setVisible(False)
        _layout.addWidget(_dropHere)

        if stretch:
            _layout.addStretch(0)

    def isVertical(self):
        _dir = self.layout().direction();
        return (_dir == QBoxLayout.Direction.TopToBottom) or (_dir == QBoxLayout.Direction.BottomToTop)

    def propagateMinimumDimension(self):
        margins = self.contentsMargins()
        current_dim = 100
        widget = self
        while (isinstance(widget,QWidgetListWidget)):
            items = widget.get_items()
            scroll = widget
            if self.isVertical:
                dim = 'width'
                set_min_dim = 'setMinimumWidth'
            else:
                dim = 'height'
                set_min_dim = 'setMinimumHeight'

            dims = tuple(getattr(w.sizeHint(),dim)() for w in items)
            max_dim = max(dims)
            max_dim_item = items[dims.index(max_dim)]

            new_dim = max_dim + margins.left() + margins.right()
            current_dim = max(current_dim,new_dim)
            getattr(scroll,set_min_dim)(current_dim)

            widget = widget.parentWidget()


    def get_items(self,only_selected = False):
        widgets = []
        layout = self.layout()
        c = layout.count()
        for _id in range(layout.count()):
            item = layout.itemAt(_id)
            widget = item.widget()
            if isinstance(widget,QWidgetListItem):
                if (not only_selected) or (widget.isSelected()):
                    widgets.append(widget)
        return widgets

    def add_item(self,item : QWidgetListItem, index : int = -1):
        layout = self.layout()
        n_elements = layout.count()
        if (index < 0) or (index >= n_elements):
            index = n_elements -1

        layout.insertWidget(index,item)

        margins = self.contentsMargins()
        min_width = max(self.minimumWidth(),item.sizeHint().width() + margins.left() + margins.right())
        self.setMinimumWidth(min_width)
        self.propagateMinimumDimension()
        self.setLayout(layout)
        return item

    def remove_item(self,item : QWidgetListItem):
        layout = self.layout()
        item.setParent(None)
        layout.removeWidget(item)
        layout.update()

    def get_selected_items(self):
        return self.get_items(only_selected = True)

