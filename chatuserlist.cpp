//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatUserList.h" resolved

#include "chatuserlist.h"
#include "ui_ChatUserList.h"
#include <QEvent>
#include <QScrollBar>
#include <QWheelEvent>

ChatUserList::ChatUserList(QWidget* parent) :
  QListWidget(parent) {
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  viewport()->installEventFilter(this);
}

ChatUserList::~ChatUserList() {
}

bool ChatUserList::eventFilter(QObject* watched, QEvent* event) {
  // 检查事件是否是鼠标悬浮进入或离开
  if (watched != viewport())
    return QListWidget::eventFilter(watched, event);

  if (event->type() == QEvent::Enter) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  } else if (event->type() == QEvent::Leave) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  } else if (event->type() == QEvent::Wheel) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    const auto wheel_event = dynamic_cast<QWheelEvent*>(event);
    const int num_degrees = wheel_event->angleDelta().y() / 8;
    const int num_steps = num_degrees / 15;

    const auto max_scroll_value = verticalScrollBar()->maximum();
    const auto current_value = verticalScrollBar()->value() - num_steps;

    // 设置滚动幅度
    verticalScrollBar()->setValue(current_value);

    // 检查是否滚动到底部
    if (current_value > max_scroll_value) {
      emit sig_loading_chat_user();
    }
    return true;
  }

  return QListWidget::eventFilter(watched, event);
}
