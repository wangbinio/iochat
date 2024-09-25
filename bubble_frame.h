//
// Created by summer on 2024/9/25.
//

#ifndef BUBBLE_FRAME_H
#define BUBBLE_FRAME_H

#include <QFrame>
#include <QHBoxLayout>

#include "global.h"

class BubbleFrame : public QFrame {
  Q_OBJECT

public:
  explicit BubbleFrame(ChatRole role, QWidget* parent = nullptr);
  void setMargin(int margin);
  void setWidget(QWidget* widget);

protected:
  void paintEvent(QPaintEvent* event) override;

private:
  QHBoxLayout* layout_;
  ChatRole role_;
  int margin_;
};


#endif //BUBBLE_FRAME_H
