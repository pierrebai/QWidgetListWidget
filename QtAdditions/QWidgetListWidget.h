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
      void Clear();

      // Add a widget item.
      QWidgetListItem* AddItem(QWidgetListItem* item, int index = -1);

      // Remove a widget item.
      void RemoveItem(QWidgetListItem* item);

      // Retrieve all widget items kept directly in this list widget.
      std::vector<QWidgetListItem*> GetItems() const;

   protected:
      virtual QWidgetListItem* CloneItem(QWidgetListItem*) const;

      void dragEnterEvent(QDragEnterEvent* event) override;
      void dragLeaveEvent(QDragLeaveEvent* event) override;
      void dragMoveEvent(QDragMoveEvent* event) override;
      void dropEvent(QDropEvent* event) override;
      void mousePressEvent(QMouseEvent* event) override;
      void childEvent(QChildEvent* event) override;

      QWidgetListItem* FindWidgetAt(const QPoint& pt) const;

      void UpdateDropHereLabel();
      void PropagateMinimumWidth();

      ListModifiedCallbackFunction _modifCallback;
      QVBoxLayout* _layout = nullptr;
      QLabel* _dropHere = nullptr;
   };
}
