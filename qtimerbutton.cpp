//
// Created by summer on 2024/9/10.
//

#include "qtimerbutton.h"
#include <QMouseEvent>

QTimerButton::QTimerButton(QWidget* parent) : QPushButton(parent), count_(10) {
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, [this] {
    count_--;
    if (count_ <= 0) {
      timer_->stop();
      count_ = 10;
      setText("获取");
      setEnabled(true);
    } else {
      setText(QString("获取(%1)").arg(count_));
    }
  });
}

QTimerButton::~QTimerButton() {
  timer_->stop();
}

void QTimerButton::Stop() {
  timer_->stop();
  count_ = 10;
  setText("获取");
  setEnabled(true);
}

void QTimerButton::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    setEnabled(false);
    setText(QString("获取(%1)").arg(count_));
    timer_->start(1000);
    emit clicked();
  }
  QPushButton::mouseReleaseEvent(event);
}
