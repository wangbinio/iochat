//
// Created by summer on 2024/9/10.
//

#ifndef TIMER_BUTTON_H
#define TIMER_BUTTON_H

#include <QPushButton>
#include <QTimer>

class QTimerButton : public QPushButton {
  Q_OBJECT
public:
  QTimerButton(QWidget* parent = nullptr);
  ~QTimerButton();

  void Stop();

  void mouseReleaseEvent(QMouseEvent* event) override;

private:
  QTimer* timer_;
  int count_;
};


#endif //TIMER_BUTTON_H
