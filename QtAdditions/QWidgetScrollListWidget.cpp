#include "QWidgetScrollListWidget.h"
#include "QWidgetListMimeData.h"

namespace QtAdditions
{
   QWidgetScrollListWidget::QWidgetScrollListWidget(QWidget* widget, QWidget* parent)
   : QScrollArea(parent)
   {
      setWidget(widget);
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
      setWidgetResizable(true);
      setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
      setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
   }

}

