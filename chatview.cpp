//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatView.h" resolved

#include "chatview.h"

#include <QEvent>
#include <QPainter>
#include <QScrollBar>
#include <QStyleOption>
#include <QTimer>

ChatView::ChatView(QWidget* parent) : QWidget(parent) {
  const auto mainLayout = new QVBoxLayout();
  mainLayout->setMargin(0);
  this->setLayout(mainLayout);

  scrollArea_ = new QScrollArea();
  scrollArea_->setObjectName("chat_area");
  mainLayout->addWidget(scrollArea_);

  const auto w = new QWidget(this);
  w->setObjectName("chat_bg");
  w->setAutoFillBackground(true);

  chatItemLayout_ = new QVBoxLayout(w);
  chatItemLayout_->addWidget(new QWidget(), 100000);
  w->setLayout(chatItemLayout_);
  scrollArea_->setWidget(w);

  scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  const auto scroll_bar = scrollArea_->verticalScrollBar();
  scroll_bar->setHidden(true);
  connect(scroll_bar, &QScrollBar::rangeChanged, this,
      &ChatView::onScrollBarMoved);

  const auto h_layout_1 = new QHBoxLayout();
  h_layout_1->setMargin(0);
  h_layout_1->addWidget(scroll_bar, 0, Qt::AlignRight);
  scrollArea_->setLayout(h_layout_1);

  scrollArea_->setWidgetResizable(true);
  scrollArea_->installEventFilter(this);
}

void ChatView::appendChatItem(QWidget* item) {
  chatItemLayout_->insertWidget(chatItemLayout_->count() - 1, item);
  append_ = true;
}

void ChatView::prependChatItem(QWidget* item) {
  chatItemLayout_->insertWidget(0, item);
  append_ = true;
}

void ChatView::insertChatItem(QWidget* before, QWidget* item) {
}

bool ChatView::eventFilter(QObject* watched, QEvent* event) {
  if (watched == scrollArea_ && event->type() == QEvent::Enter) {
    scrollArea_->verticalScrollBar()->setHidden(
        scrollArea_->verticalScrollBar()->maximum() == 0);
  } else if (watched == scrollArea_ && event->type() == QEvent::Leave) {
    scrollArea_->verticalScrollBar()->setHidden(true);
  }
  return QWidget::eventFilter(watched, event);
}

void ChatView::paintEvent(QPaintEvent* event) {
  QStyleOption option;
  option.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ChatView::onScrollBarMoved(int min, int max) {
  if (append_) {
    const auto scroll_bar = scrollArea_->verticalScrollBar();
    scroll_bar->setSliderPosition(scroll_bar->maximum());

    QTimer::singleShot(500, [this] {
      append_ = false;
    });
  }
}
