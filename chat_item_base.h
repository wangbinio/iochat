//
// Created by summer on 2024/9/25.
//

#ifndef CHAT_ITEM_BASE_H
#define CHAT_ITEM_BASE_H

#include <QLabel>
#include <QWidget>
#include "global.h"

class ChatItemBase : public QWidget {
  Q_OBJECT

public:
  explicit ChatItemBase(ChatRole role, QWidget* parent = nullptr);
  void setUserName(const QString& userName) const;
  void setUserIcon(const QPixmap& icon) const;
  void setWidget(QWidget* widget);

private:
  ChatRole role_;
  QLabel* name_label_;
  QLabel* icon_label_;
  QWidget* bubble_;
};


#endif //CHAT_ITEM_BASE_H
