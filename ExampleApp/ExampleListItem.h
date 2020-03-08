#pragma once

#ifndef EXAMPLE_APP_LIST_ITEM_H
#define EXAMPLE_APP_LIST_ITEM_H

#include "QWidgetListItem.h"

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qpushbutton.h>

namespace ExampleApp
{
   using QWidgetListItem = QtAdditions::QWidgetListItem;

   struct ExampleListItem : QWidgetListItem
   {
      ExampleListItem(const QString& text, bool isChecked = false);

      ExampleListItem* clone() const override;

   private:
      QLabel*      _nameLabel  = nullptr;
      QLineEdit*   _textEdit   = nullptr;
      QPushButton* _editButton = nullptr;
      QCheckBox*   _includeBox = nullptr;
   };
}

#endif
