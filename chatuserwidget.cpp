//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatUserWidget.h" resolved

#include "chatuserwidget.h"
#include "ui_ChatUserWidget.h"


ChatUserWidget::ChatUserWidget(QWidget* parent) :
  ListItemBase(parent), ui(new Ui::ChatUserWidget) {
  ui->setupUi(this);
  setItemType(CHAT_USER_ITEM);
}

ChatUserWidget::~ChatUserWidget() {
  delete ui;
}

QSize ChatUserWidget::sizeHint() const {
  return {240, 60};
}

void ChatUserWidget::setInfo(const QString& name, const QString& head,
    const QString& message) {
  name_ = name;
  head_ = head;
  message_ = message;

  const QPixmap pixmap(head_);
  ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio,
      Qt::SmoothTransformation));
  ui->icon_lb->setScaledContents(true);

  ui->user_name_lb->setText(name_);
  ui->user_chat_lb->setText(message_);
}
