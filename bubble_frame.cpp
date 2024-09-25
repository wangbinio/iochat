//
// Created by summer on 2024/9/25.
//

#include "bubble_frame.h"

#include <QPainter>

constexpr int triangle_width = 8;

BubbleFrame::BubbleFrame(const ChatRole role, QWidget* parent) : QFrame(parent),
  role_(role), margin_(3) {
  layout_ = new QHBoxLayout();
  if (role_ == ChatRole::kSelf) {
    layout_->setContentsMargins(margin_, margin_, margin_ + triangle_width,
        margin_);
  } else {
    layout_->setContentsMargins(margin_ + triangle_width, margin_, margin_,
        margin_);
  }

  setLayout(layout_);
}

void BubbleFrame::setMargin(const int margin) {
  Q_UNUSED(margin);
  margin_ = margin;
}

void BubbleFrame::setWidget(QWidget* widget) {
  if (layout_->count() == 0) {
    layout_->addWidget(widget);
  }
}

void BubbleFrame::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setPen(Qt::NoPen);

  if (role_ == ChatRole::kSelf) {
    const QColor color(158, 234, 106);
    painter.setBrush(color);
    const QRect rect(0, 0, width() - triangle_width, height());
    painter.drawRoundedRect(rect, 5, 5);

    const QPoint points[3] = {
        {rect.x() + rect.width(), 12},
        {rect.x() + rect.width(), 12 + triangle_width + 2},
        {rect.x() + rect.width() + triangle_width, 10 + triangle_width / 2}
    };
    painter.drawPolygon(points, 3);
  } else {
    const QColor color(Qt::white);
    painter.setBrush(color);
    const QRect rect(triangle_width, 0, width() - triangle_width, height());
    painter.drawRoundedRect(rect, 5, 5);

    const QPoint points[3] = {
        {rect.x(), 12},
        {rect.x(), 12 + triangle_width + 2},
        {rect.x() - triangle_width, 10 + triangle_width / 2}
    };
    painter.drawPolygon(points, 3);
  }
  QFrame::paintEvent(event);
}
