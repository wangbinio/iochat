//
// Created by summer on 2024/9/25.
//

#ifndef PICTURE_BUBBLE_H
#define PICTURE_BUBBLE_H

#include "bubble_frame.h"
#include <QPixmap>

class PictureBubble : public BubbleFrame {
  Q_OBJECT

public:
  explicit PictureBubble(ChatRole role, const QPixmap& pic, QWidget* parent =
      nullptr);
};


#endif //PICTURE_BUBBLE_H
