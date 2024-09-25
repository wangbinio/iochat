//
// Created by summer on 2024/9/25.
//

#ifndef TEXT_BUBBLE_H
#define TEXT_BUBBLE_H

#include "bubble_frame.h"
#include <QTextEdit>

class TextBubble : public BubbleFrame {
  Q_OBJECT

public:
  explicit TextBubble(ChatRole role, const QString& text, QWidget* parent =
      nullptr);

protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

private:
  void adjustTextHeight();
  void setPlainText(const QString& text);
  void initStyleSheet();

  QTextEdit* text_edit_;
};


#endif //TEXT_BUBBLE_H
