//
// Created by summer on 2024/9/22.
//

#ifndef LIST_ITEM_BASE_H
#define LIST_ITEM_BASE_H

#include <QWidget>
#include "global.h"

class ListItemBase : public QWidget {
  Q_OBJECT

public:
  explicit ListItemBase(QWidget* parent = nullptr);
  void paintEvent(QPaintEvent* event) override;
  void setItemType(ListItemType type);
  ListItemType itemType() const;

public slots:
signals:

private:
  ListItemType item_type_;
};


#endif //LIST_ITEM_BASE_H
