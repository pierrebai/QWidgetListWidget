#include "ExampleListItem.h"

#include <QtWidgets/qboxlayout.h>
#include <QtGui/qpainter.h>
#include <QtGui/qpixmap.h>

namespace ExampleApp
{
   using namespace std;
   using namespace QtAdditions;

   ExampleListItem::ExampleListItem(const QString& text, bool isChecked)
   {
      setToolTip("example item");
      setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

      auto top_layout = new QHBoxLayout(this);
      top_layout->setMargin(0);
      setLayout(top_layout);

      auto pixmap = QPixmap(8, 32);
      {
         QPainter painter(&pixmap);
         painter.fillRect(pixmap.rect().adjusted(0, 0, 0, 0), QColor(208, 208, 208, 128));
      }
      auto handle = new QLabel;
      handle->setPixmap(pixmap);
      handle->setScaledContents(true);
      handle->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred));
      handle->setMargin(2);
      top_layout->addWidget(handle);

      auto container_layout = new QVBoxLayout;
      container_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
      container_layout->setMargin(4);
      top_layout->addLayout(container_layout);

      auto name_layout = new QHBoxLayout;
      name_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
      name_layout->setMargin(0);
      container_layout->addLayout(name_layout);

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
      auto newItem = new ExampleListItem(_textEdit->text(), _includeBox->isChecked());
      return newItem;
   }

}

