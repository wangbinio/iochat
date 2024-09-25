//
// Created by summer on 2024/9/25.
//

#include "chat_item_base.h"

#include <QGridLayout>

ChatItemBase::ChatItemBase(const ChatRole role, QWidget* parent):
  QWidget(parent),
  role_(role), name_label_(nullptr), icon_label_(nullptr), bubble_(nullptr) {
  name_label_ = new QLabel(this);
  name_label_->setObjectName("chat_user_name");
  const QFont font("Microsoft YaHei", 9);
  name_label_->setFont(font);
  name_label_->setFixedHeight(20);

  icon_label_ = new QLabel(this);
  icon_label_->setScaledContents(true);
  icon_label_->setFixedSize(42, 42);

  bubble_ = new QWidget();

  const auto spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding,
      QSizePolicy::Minimum);

  const auto layout = new QGridLayout();
  layout->setVerticalSpacing(3);
  layout->setHorizontalSpacing(3);
  layout->setMargin(3);

  if (role_ == ChatRole::kSelf) {
    name_label_->setContentsMargins(0, 0, 8, 0);
    name_label_->setAlignment(Qt::AlignRight);
    layout->addWidget(name_label_, 0, 1, 1, 1);
    layout->addWidget(icon_label_, 0, 2, 2, 1, Qt::AlignTop);
    layout->addWidget(bubble_, 1, 1, 1, 1);
    layout->addItem(spacer, 1, 0, 1, 1);
    layout->setColumnStretch(0, 2);
    layout->setColumnStretch(1, 3);
  } else {
    name_label_->setContentsMargins(8, 0, 0, 0);
    name_label_->setAlignment(Qt::AlignLeft);
    layout->addWidget(name_label_, 0, 1, 1, 1);
    layout->addWidget(icon_label_, 0, 0, 2, 1, Qt::AlignTop);
    layout->addWidget(bubble_, 1, 1, 1, 1);
    layout->addItem(spacer, 1, 2, 1, 1);
    layout->setColumnStretch(2, 2);
    layout->setColumnStretch(1, 3);
  }

  setLayout(layout);
}

void ChatItemBase::setUserName(const QString& userName) const {
  name_label_->setText(userName);
}

void ChatItemBase::setUserIcon(const QPixmap& icon) const {
  icon_label_->setPixmap(icon);
}

void ChatItemBase::setWidget(QWidget* widget) {
  const auto layout = this->layout();
  layout->replaceWidget(bubble_, widget);
  delete bubble_;
  bubble_ = widget;
}
