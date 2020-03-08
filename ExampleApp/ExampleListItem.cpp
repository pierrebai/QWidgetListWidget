#include "ExampleListItem.h"

#include <QtWidgets/qboxlayout.h>

namespace ExampleApp
{
   using namespace std;
   using namespace QtAdditions;

   ExampleListItem::ExampleListItem(const QString& text, bool isChecked)
   {
      setToolTip("example item");
      setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

      auto container_layout = new QVBoxLayout(this);
      container_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
      container_layout->setMargin(4);
      setLayout(container_layout);

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

