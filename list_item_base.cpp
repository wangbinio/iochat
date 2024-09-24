//
// Created by summer on 2024/9/22.
//

#include "list_item_base.h"
#include <QPainter>
#include <QStyleOption>

ListItemBase::ListItemBase(QWidget* parent) : QWidget(parent), item_type_
                                              (CHAT_USER_ITEM) {
}

void ListItemBase::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  QStyleOption option;
  option.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ListItemBase::setItemType(const ListItemType type) {
  item_type_ = type;
}

ListItemType ListItemBase::itemType() const {
  return item_type_;
}
