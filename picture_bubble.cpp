//
// Created by summer on 2024/9/25.
//

#include "picture_bubble.h"

#include <QLabel>

static constexpr int pic_width = 160;
static constexpr int pic_height = 90;

PictureBubble::PictureBubble(const ChatRole role, const QPixmap& pic,
    QWidget* parent): BubbleFrame(role, parent) {
  const auto label = new QLabel(this);
  label->setScaledContents(true);

  const auto pix = pic.scaled({pic_width, pic_height}, Qt::KeepAspectRatio);
  label->setPixmap(pix);

  setWidget(label);

  const auto left_margin = layout()->contentsMargins().left();
  const auto right_margin = layout()->contentsMargins().right();
  const auto bottom_margin = layout()->contentsMargins().bottom();

  setFixedSize(pic_width + left_margin + right_margin,
      pic_height + bottom_margin * 2);
}
