from PySide2.QtWidgets import QWidget
from PySide2.QtGui import QPalette

fu = 0
_DefaultBackground = False
_HighBackground = False
_SelectedBackground = False
colores_initialized = False
_HighlightedItems = []


class QWidgetListItem(QWidget):
    def __init__(self, parent : QWidget = None ):
        current_module = __import__(__name__)
        super().__init__(parent)
        self.is_selected = False

        self.setBackgroundRole(QPalette.ColorRole.Base)
        self.setAutoFillBackground(True)

        print(current_module.colores_initialized)
        if ~current_module.colores_initialized:
            current_module._DefaultBackground = self.palette()
            current_module._HighBackground = self.palette()
            current_module._HighBackground.setColor(QPalette.ColorRole.Base,current_module._HighBackground.color(QPalette.Highlight).lighter(210))

            current_module._SelectedBackground = self.palette()
            _SelectedBackground.setColor(QPalette.ColorRole.Base, current_module._SelectedBackground.color(QPalette.Highlight))
            current_module.colores_initialized = True
        

    def __del__(self):
        self.remove_self_from_highlighted_items()
    
    def clone(self):
        return QWidgetListItem(self.parent)
    
    def enterEvent(self,event):
        super().enterEvent(event)
        self.highlight_background()
    def leaveEvent(self,event):
        super().leaveEvent(event)
        self.remove_highlighted_background()

    def remove_self_from_highlighted_items(self):
        try:
            pos = _HighlightedItems.index(self)
            _HighlightedItems.pop(pos)
        except ValueError:
            pass

    def highlight_background(self):
        if len(_HighlightedItems)>0:
            last_element = _HighlightedItems[-1]
            if last_element.is_selected:
                last_element.setPalette(_SelectedBackground)
            else:
                last_element.setPalette(_DefaultBackground)
            last_element.update()
            
        self.setPalette(_SelectedBackground)
        _HighlightedItems.append(self)
        
    def remove_highlighted_background(self):
        if self.is_selected:
            self.setPalette(_SelectedBackground)
        else:
            self.setPalette(_DefaultBackground)

        self.remove_self_from_highlighted_items

        if len(_HighlightedItems)>0:
            last_element = _HighlightedItems[-1]
            last_element.setPalette(_HighBackground)
            last_element.update()

