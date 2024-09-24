//
// Created by summer on 2024/9/22.
//

#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H

#include <QPushButton>


QT_BEGIN_NAMESPACE

namespace Ui {
class ClickedBtn;
}

QT_END_NAMESPACE

class ClickedBtn : public QPushButton {
  Q_OBJECT

public:
  explicit ClickedBtn(QWidget* parent = nullptr);
  ~ClickedBtn() override;

  void setState(QString normal, QString hover, QString press);

protected:
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

  void updateState(QString state);

private:
  QString normal_;
  QString hover_;
  QString press_;
};


#endif //CLICKEDBTN_H
