#include "dak/QtAdditions/QWidgetListWidget.h"
#include "dak/QtAdditions/QWidgetScrollListWidget.h"
#include "dak/QtAdditions/QWidgetListMimeData.h"

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>

#include <QtGui/qdrag.h>
#include <QtGui/qevent.h>
#include <QtGui/qwindow.h>

#include <QtCore/qtimer.h>

#include <algorithm>

namespace dak::QtAdditions
{
   using namespace std;

   /////////////////////////////////////////////////////////////////////////
   //
   // Widget list panel.

   QWidgetListWidget::QWidgetListWidget(ListModifiedCallbackFunction modifCallback, bool stretch, QBoxLayout::Direction dir, QWidget* parent)
   : QFrame(parent), _modifCallback(modifCallback)
   {
      setBackgroundRole(QPalette::ColorRole::Base);
      setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
      setMinimumSize(QSize(20, 20));
      if (!stretch)
         setFrameStyle(QFrame::Box);

      _layout = new QBoxLayout(dir);
      _layout->setSizeConstraint(QLayout::SetMinimumSize);
      _layout->setMargin(2);
      _layout->setSpacing(0);
      setLayout(_layout);

      _dropHere = new QLabel(QString("Drop items here."));
      _dropHere->setForegroundRole(QPalette::ColorRole::Mid);
      _dropHere->setVisible(false);
      _layout->addWidget(_dropHere);

      if (stretch)
         _layout->addStretch(0);
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Minimum size propagation.

   bool QWidgetListWidget::isVertical() const
   {
      const auto dir = _layout->direction();
      return dir == QBoxLayout::Direction::TopToBottom || dir == QBoxLayout::Direction::BottomToTop;
   }

   void QWidgetListWidget::propagateMinimumDimension()
   {
      int minSoFar = 0;
      QWidget* widget = this;
      while (widget)
      {
         if (auto scroll = dynamic_cast<QWidgetScrollListWidget*>(widget))
         {
            if (auto list = dynamic_cast<QWidgetListWidget*>(scroll->widget()))
            {
               auto items = list->getItems();
               if (isVertical())
               {
                  auto maxMinWidthPos = max_element(items.begin(), items.end(), [](const QWidgetListItem* lhs, const QWidgetListItem* rhs)
                  {
                     return lhs->sizeHint().width() < rhs->sizeHint().width();
                  });

                  if (maxMinWidthPos != items.end())
                  {
                     const int newWidth = (*maxMinWidthPos)->sizeHint().width() + scroll->contentsMargins().left() + scroll->contentsMargins().right();
                     minSoFar = max(minSoFar, newWidth);
                     scroll->setMinimumWidth(minSoFar);
                  }
               }
               else
               {
                  auto maxMinHeightPos = max_element(items.begin(), items.end(), [](const QWidgetListItem* lhs, const QWidgetListItem* rhs)
                  {
                     return lhs->sizeHint().height() < rhs->sizeHint().height();
                  });

                  if (maxMinHeightPos != items.end())
                  {
                     const int newHeight = (*maxMinHeightPos)->sizeHint().height() + scroll->contentsMargins().left() + scroll->contentsMargins().right();
                     minSoFar = max(minSoFar, newHeight);
                     scroll->setMinimumHeight(minSoFar);
                  }

               }
            }
         }
         widget = widget->parentWidget();
      }
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Items management.

   void QWidgetListWidget::clear()
   {
      for (auto child : getItems())
         delete child;

      if (_modifCallback)
         _modifCallback(this);
   }

   QWidgetListItem* QWidgetListWidget::addItem(QWidgetListItem* item, int index)
   {
      if (!item)
         return nullptr;

      if (!_layout)
         return nullptr;

      if (index < 0 || index >= _layout->count())
         index = _layout->count() - 1;

      _layout->insertWidget(index, item);

      setMinimumWidth(max(minimumWidth(), item->sizeHint().width() + contentsMargins().left() + contentsMargins().right()));

      propagateMinimumDimension();

      if (_modifCallback)
         _modifCallback(this);

      return item;
   }

   void QWidgetListWidget::removeItem(QWidgetListItem* item)
   {
      item->setParent(nullptr);
      _layout->removeWidget(item);
      _layout->update();

      if (_modifCallback)
         _modifCallback(this);
   }

   vector<QWidgetListItem*> QWidgetListWidget::getItems(bool onlySelected) const
   {
      vector<QWidgetListItem*> widgets;

      const int c = _layout->count();
      for (int i = 0; i < c; ++i)
         if (auto w = dynamic_cast<QWidgetListItem*>(_layout->itemAt(i)->widget()))
            if (!onlySelected || w->isSelected())
               widgets.push_back(w);

      return widgets;
   }

   std::vector<QWidgetListItem*> QWidgetListWidget::getSelectedItems() const
   {
      return getItems(true);
   }

   /////////////////////////////////////////////////////////////////////////
   //
   // Drag and drop.

   QWidgetListItem* QWidgetListWidget::cloneItem(QWidgetListItem* item) const
   {
      if (!item)
         return nullptr;

      return item->clone();
   }

   void QWidgetListWidget::dragEnterEvent(QDragEnterEvent* event)
   {
      const QWidgetListMimeData* mime = dynamic_cast<const QWidgetListMimeData*>(event->mimeData());
      if (!mime)
         return event->ignore();

      if (event->source() == this)
      {
         event->setDropAction(Qt::MoveAction);
         event->accept();
      }
      else
      {
         event->acceptProposedAction();
      }
   }

   void QWidgetListWidget::dragLeaveEvent(QDragLeaveEvent* event)
   {
      event->accept();
   }

   void QWidgetListWidget::dragMoveEvent(QDragMoveEvent* event)
   {
      const QWidgetListMimeData* mime = dynamic_cast<const QWidgetListMimeData*>(event->mimeData());
      if (!mime)
         return event->ignore();

      event->setDropAction(Qt::MoveAction);
      event->accept();
   }

   void QWidgetListWidget::dropEvent(QDropEvent* event)
   {
      const QWidgetListMimeData* mime = dynamic_cast<const QWidgetListMimeData*>(event->mimeData());
      if (!mime)
         return event->ignore();

      const QPoint position = event->pos();
      QWidgetListItem* dropOn = findWidgetAt(position);
      const bool dropAbove = dropOn ? (position.y() < dropOn->pos().y() + dropOn->size().height() / 2) : false;
      const int dropIndexOffset = dropAbove ? 0 : 1;
      const int dropOnIndex = dropOn ? _layout->indexOf(dropOn) : -1000;

      const bool sameSource = event->source() == this;

      if (sameSource || event->proposedAction() == Qt::MoveAction)
      {
         // Remove panel and insert it at correct position in list.
         auto movedWidget = mime->Widget;
         if (movedWidget && movedWidget != dropOn)
         {
            const int movedIndex = _layout->indexOf(movedWidget);
            const int dropAdjust = sameSource ? (movedIndex < dropOnIndex ? 1 : 0) : 0;
            const int newIndex = dropOnIndex + dropIndexOffset - dropAdjust;
            movedWidget->setParent(nullptr);
            _layout->removeWidget(movedWidget);
            addItem(movedWidget, newIndex);
         }
         else
         {
            movedWidget->select(!movedWidget->isSelected());
         }
         event->setDropAction(Qt::MoveAction);
         event->accept();
      }
      else
      {
         auto newWidget = cloneItem(mime->Widget);
         if (newWidget)
         {
            const int newIndex = dropOnIndex + dropIndexOffset;
            addItem(newWidget, newIndex);
         }
         event->acceptProposedAction();
      }
   }

   void QWidgetListWidget::mousePressEvent(QMouseEvent* event)
   {
      QWidgetListItem* widget = findWidgetAt(event->pos());
      if (!widget)
         return;

      QWidgetListMimeData* mimeData = new QWidgetListMimeData;
      mimeData->Widget = widget;
      mimeData->HotSpot = event->pos() - widget->pos();
      mimeData->setData(QWidgetListMimeData::MimeType, QByteArray());

      qreal dpr = window()->windowHandle()->devicePixelRatio();
      QPixmap pixmap(widget->size() * dpr);
      pixmap.setDevicePixelRatio(dpr);
      widget->render(&pixmap);

      QDrag* drag = new QDrag(this);
      drag->setMimeData(mimeData);
      drag->setPixmap(pixmap);
      drag->setHotSpot(mimeData->HotSpot);

      if (acceptDrops())
         Qt::DropAction dropAction = drag->exec(Qt::MoveAction, Qt::MoveAction);
      else
         Qt::DropAction dropAction = drag->exec(Qt::CopyAction, Qt::CopyAction);
   }

   void QWidgetListWidget::mouseReleaseEvent(QMouseEvent* event)
   {
      QWidgetListItem* widget = findWidgetAt(event->pos());
      if (!widget)
         return;

      widget->select(!widget->isSelected());
   }

   QWidgetListItem* QWidgetListWidget::findWidgetAt(const QPoint& pt) const
   {
      for (auto child = childAt(pt); child; child = child->parentWidget())
         if (auto widget = dynamic_cast<QWidgetListItem*>(child))
            return widget;

      return nullptr;
   }

   void QWidgetListWidget::childEvent(QChildEvent* event)
   {
      QFrame::childEvent(event);

      if (event->type() == QEvent::ChildRemoved || event->type() == QEvent::ChildAdded)
      {
         QTimer::singleShot(1, [self = this]()
         {
            self->updateDropHereLabel();
            self->propagateMinimumDimension();
         });
      }
   }

   void QWidgetListWidget::updateDropHereLabel()
   {
      if (!_dropHere)
         return;

      _dropHere->setVisible(acceptDrops() && getItems().size() <= 0);
   }
}

