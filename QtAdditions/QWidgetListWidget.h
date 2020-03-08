#pragma once

#include "QWidgetListItem.h"

#include <QtWidgets/qframe.h>

#include <functional>

class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
class QVBoxLayout;
class QLabel;

namespace QtAdditions
{
   /////////////////////////////////////////////////////////////////////////
   //
   // List widget that contains complex widgets.

   struct QWidgetListWidget : public QFrame
   {
      // Callback signature when the list was modified: added or remove an item.
      using ListModifiedCallbackFunction = std::function<void(QWidgetListWidget * list)>;;

      // Create a widget list widget.
      QWidgetListWidget(ListModifiedCallbackFunction modifCallback = {}, bool stretch = true, QWidget * parent = nullptr);

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
      virtual QWidgetListItem* cloneItem(QWidgetListItem*) const;

      void dragEnterEvent(QDragEnterEvent* event) override;
      void dragLeaveEvent(QDragLeaveEvent* event) override;
      void dragMoveEvent(QDragMoveEvent* event) override;
      void dropEvent(QDropEvent* event) override;
      void mousePressEvent(QMouseEvent* event) override;
      void mouseReleaseEvent(QMouseEvent* event) override;
      void childEvent(QChildEvent* event) override;

      QWidgetListItem* findWidgetAt(const QPoint& pt) const;

      void updateDropHereLabel();
      void propagateMinimumWidth();

      ListModifiedCallbackFunction _modifCallback;
      QVBoxLayout* _layout = nullptr;
      QLabel* _dropHere = nullptr;
   };
}
