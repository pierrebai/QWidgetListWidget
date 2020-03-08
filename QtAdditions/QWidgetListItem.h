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

      virtual QWidgetListItem* Clone() const;

   protected:
      void enterEvent(QEvent* event) override;
      void leaveEvent(QEvent* event) override;

      void HighlightBackground(bool high);

   };
}
