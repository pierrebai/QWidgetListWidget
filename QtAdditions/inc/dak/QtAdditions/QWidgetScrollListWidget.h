#pragma once

#ifndef QT_ADDITIONS_QWIDGET_SCROLL_LIST_WIDGET_H
#define QT_ADDITIONS_QWIDGET_SCROLL_LIST_WIDGET_H

#include <QtWidgets/qscrollarea.h>

class QWidget;

namespace dak::QtAdditions
{
   /////////////////////////////////////////////////////////////////////////
   //
   // Scrollable widget.
   //
   // Use it to wrap the QWidgetListWidget to provide a scrollable list.
   // The list widget is not scrollable by itself so that it can be embedded
   // within its own items if needed to provide recursive lists.

   struct QWidgetScrollListWidget : public QScrollArea
   {
      // Create a scrollable widget around another widget.
      QWidgetScrollListWidget(QWidget * widget, QWidget* parent = nullptr);
   };
}

#endif
