//
// Created by summer on 2024/9/25.
//

#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "global.h"
#include <QLabel>


class StateWidget : public QWidget {
  Q_OBJECT

public:
  explicit StateWidget(QWidget* parent = nullptr);
  ~StateWidget() override;

  void setState(const QString& normal = "", const QString& hover = "",
      const QString& press = "",
      const QString& select = "", const QString& select_hover = "",
      const QString& select_press = "");
  ClickLbState getCurSate() const;
  void clearState();
  void setSelected(bool selected);
  void addRedPoint();
  void showRedPoint(bool show);
signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  void updateState(const QString& state);

  ClickLbState cur_state_;
  QString normal_;
  QString normal_hover_;
  QString normal_press_;
  QString selected_;
  QString selected_hover_;
  QString selected_press_;
  QLabel* red_point_;
};


#endif //STATEWIDGET_H
