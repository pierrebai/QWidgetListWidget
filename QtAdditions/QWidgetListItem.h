#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qscrollarea.h>

namespace QtAdditions
{
   /////////////////////////////////////////////////////////////////////////
   //
   // Complex widget kept in a list widget.

   struct QWidgetListItem : QWidget
   {
      QWidgetListItem(QWidget* parent = nullptr);

      bool isSelected() const { return _selected; }
      void select(bool sel) { _selected = sel; update(); }

      virtual QWidgetListItem* clone() const;

   protected:
      void enterEvent(QEvent* event) override;
      void leaveEvent(QEvent* event) override;

      void HighlightBackground(bool high);

      bool _selected = false;
   };
}
