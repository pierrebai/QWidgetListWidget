#include "ExampleListItem.h"

#include <QtWidgets/qboxlayout.h>
#include <QtGui/qpainter.h>
#include <QtGui/qpixmap.h>

namespace ExampleApp
{
   using namespace std;
   using namespace QtAdditions;

   /////////////////////////////////////////////////////////////////////////
   //
   // A simple widget that draws diagonal lines to represent an area
   // the user can grab to drag-and-drop.
   //
   // Ensures there is at least this area that can be grabbed in the
   // ExampleListItem.

   struct Grabber : QWidget
   {
      void paintEvent(QPaintEvent* event) override
      {
         QPen pen(QColor(180, 180, 180, 128));
         pen.setWidth(3);

         const int h = height();
         const int w = width();

         QPainter painter(this);
         painter.setPen(pen);
         static constexpr int offset = 4;
         static constexpr int diagonal = 10;
         for (int y = offset; y < h - (offset + diagonal) ; y += diagonal)
         {
            painter.drawLine(0, y, w, y + diagonal);
         }
      }
   };

   /////////////////////////////////////////////////////////////////////////
   //
   //
   ExampleListItem::ExampleListItem(const QString& text, bool isChecked)
   {
      setToolTip("example item");
      setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

      // Horizontal layout to contain the grabber and the rest of the UI.
      auto top_layout = new QHBoxLayout(this);
      top_layout->setMargin(0);
      setLayout(top_layout);

      // Grabber to always give some area to grab for drag-and-drop.
      auto handle = new Grabber;
      handle->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred));
      handle->setMinimumSize(QSize(8, 8));
      top_layout->addWidget(handle);

      // Layouts for the meaningful UI.
      auto container_layout = new QVBoxLayout;
      container_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
      container_layout->setMargin(4);
      top_layout->addLayout(container_layout);

      auto name_layout = new QHBoxLayout;
      name_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
      name_layout->setMargin(0);
      container_layout->addLayout(name_layout);

      // The UI.
      _nameLabel = new QLabel("Label");
      name_layout->addWidget(_nameLabel);

      _textEdit = new QLineEdit(text);
      name_layout->addWidget(_textEdit);

      _editButton = new QPushButton("Button");
      name_layout->addWidget(_editButton);

      _includeBox = new QCheckBox("Check");
      _includeBox->setChecked(isChecked);
      container_layout->addWidget(_includeBox);
   }

   ExampleListItem* ExampleListItem::clone() const
   {
      // The clone must duplicate the data.
      //
      // We only need to duplicate the text and check state.
      // Every thing else is constant in our example.
      auto newItem = new ExampleListItem(_textEdit->text(), _includeBox->isChecked());
      return newItem;
   }

}

