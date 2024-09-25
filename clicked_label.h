//
// Created by summer on 2024/9/10.
//

#ifndef CLICKED_LABEL_H
#define CLICKED_LABEL_H

#include <QLabel>

#include "global.h"


class ClickedLabel : public QLabel {
  Q_OBJECT

public:
  ClickedLabel(QWidget* parent = nullptr);
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void setState(const QString& normal = "", const QString& hover = "",
      const QString& press = "",
      const QString& select = "", const QString& select_hover = "",
      const QString& select_press = "");
  ClickLbState getCurSate() const;
signals:
  void clicked();

private:
  void updateState(const QString& state);

  ClickLbState cur_state_;
  QString normal_;
  QString normal_hover_;
  QString normal_press_;
  QString selected_;
  QString selected_hover_;
  QString selected_press_;
};


#endif //CLICKED_LABEL_H
