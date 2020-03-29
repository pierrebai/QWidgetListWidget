#pragma once

#ifndef EXAMPLE_APP_LIST_ITEM_H
#define EXAMPLE_APP_LIST_ITEM_H

#include "dak/QtAdditions/QWidgetListItem.h"

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qpushbutton.h>

namespace dak::ExampleApp
{
   using QWidgetListItem = QtAdditions::QWidgetListItem;

   /////////////////////////////////////////////////////////////////////////
   //
   // Example of an item put in the QWidgetListWidget.
   //
   // It's a normal widget, except in needs a clone() method to enable
   // drag-and-drop. If you dont'want to support drag-and-drop, then clone()
   // is not needed.

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
