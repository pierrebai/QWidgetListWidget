#include "QWidgetListItem.h"

#include <mutex>

namespace QtAdditions
{
   using namespace std;

   namespace
   {
      QPalette _DefaultBackground;
      QPalette _HighBackground;

      once_flag initPalettes;

      static vector<QWidgetListItem*> _HighlightedItems;
   }

   QWidgetListItem::QWidgetListItem(QWidget* parent)
   : QWidget(parent)
   {
      setBackgroundRole(QPalette::ColorRole::Base);
      setAutoFillBackground(true);

      call_once(initPalettes, [self = this]()
      {
         _DefaultBackground = self->palette();
         _HighBackground = self->palette();
         _HighBackground.setColor(QPalette::ColorRole::Base, _HighBackground.color(QPalette::Highlight).lighter(210));
      });
   }

   QWidgetListItem* QWidgetListItem::Clone() const
   {
      return new QWidgetListItem;
   }

   void QWidgetListItem::enterEvent(QEvent* event)
   {
      QWidget::enterEvent(event);
      HighlightBackground(true);
   }

   void QWidgetListItem::leaveEvent(QEvent* event)
   {
      QWidget::leaveEvent(event);
      HighlightBackground(false);
   }

   void QWidgetListItem::HighlightBackground(bool high)
   {
      if (high)
      {
         if (_HighlightedItems.size() > 0)
         {
            _HighlightedItems.back()->setPalette(_DefaultBackground);
            _HighlightedItems.back()->update();
         }

         _HighlightedItems.push_back(this);
         setPalette(_HighBackground);
      }
      else
      {
         setPalette(_DefaultBackground);
         auto pos = std::find(_HighlightedItems.begin(), _HighlightedItems.end(), this);
         if (pos != _HighlightedItems.end())
            _HighlightedItems.erase(pos);

         if (_HighlightedItems.size() > 0)
         {
            _HighlightedItems.back()->setPalette(_HighBackground);
            _HighlightedItems.back()->update();
         }
      }
      update();
   }

}

