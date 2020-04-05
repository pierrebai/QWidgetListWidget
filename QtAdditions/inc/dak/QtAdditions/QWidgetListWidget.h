#pragma once

#ifndef QT_ADDITIONS_QWIDGET_LIST_WIDGET_H
#define QT_ADDITIONS_QWIDGET_LIST_WIDGET_H

#include "dak/QtAdditions/QWidgetListItem.h"

#include <QtWidgets/qframe.h>
#include <QtWidgets/qboxlayout.h>

#include <functional>

class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
class QVBoxLayout;
class QLabel;

namespace dak::QtAdditions
{
   /////////////////////////////////////////////////////////////////////////
   //
   // List widget that contains complex widgets.

   struct QWidgetListWidget : public QFrame
   {
      // Callback signature when the list was modified: added or remove an item.
      using ListModifiedCallbackFunction = std::function<void(QWidgetListWidget * list)>;

      // Create a widget list widget.
      QWidgetListWidget(ListModifiedCallbackFunction modifCallback = {}, bool stretch = true, QBoxLayout::Direction dir = QBoxLayout::Direction::TopToBottom, QWidget * parent = nullptr);

      // Check if the list is vertical or horizontal.
      bool isVertical() const;

      // Clears the list panel of all items.
      void clear();

      // Add a widget item.
      QWidgetListItem* addItem(QWidgetListItem* item, int index = -1);

      // Remove a widget item.
      void removeItem(QWidgetListItem* item);

      // Retrieve all widget items kept directly in this list widget.
      std::vector<QWidgetListItem*> getItems(bool onlySelected = false) const;

      // Retrieve all selected widget items kept directly in this list widget.
      std::vector<QWidgetListItem*> getSelectedItems() const;

   protected:
      // Cloning an item when dropping into another list widget.
      //
      // Made virtual in case the simple clone() function on the item
      // is not sufficient and other more complicated processing is
      // needed to create a copy of an item.
      virtual QWidgetListItem* cloneItem(QWidgetListItem*) const;

      // Drag-and-drop support.
      void dragEnterEvent(QDragEnterEvent* event) override;
      void dragLeaveEvent(QDragLeaveEvent* event) override;
      void dragMoveEvent(QDragMoveEvent* event) override;
      void dropEvent(QDropEvent* event) override;
      void mousePressEvent(QMouseEvent* event) override;
      void mouseReleaseEvent(QMouseEvent* event) override;
      void childEvent(QChildEvent* event) override;

      // Helper to find the item under the mouse, for drag-and-drop.
      QWidgetListItem* findWidgetAt(const QPoint& pt) const;

      // Provides a drop-here label when the list is empty.
      // Not shown if drops (from drag-and-drop) are not enabled.
      void updateDropHereLabel();

      // Ensure the widget has enough width to show its items.
      void propagateMinimumDimension();

      ListModifiedCallbackFunction _modifCallback;
      QBoxLayout* _layout = nullptr;
      QLabel* _dropHere = nullptr;

      Q_OBJECT;
   };
}

#endif
