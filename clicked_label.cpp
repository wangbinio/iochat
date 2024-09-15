//
// Created by summer on 2024/9/10.
//

#include "clicked_label.h"

#include <QMouseEvent>

ClickedLabel::ClickedLabel(QWidget* parent): cur_state_(kNormal) {
  normal_ = "unvisible";
  normal_hover_ = "unvisible_hover";
  normal_press_ = "";
  selected_ = "visible";
  selected_hover_ = "visible_hover";
  selected_press_ = "";

  setProperty("state", normal_);
  setCursor(Qt::PointingHandCursor);
}

void ClickedLabel::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    cur_state_ = static_cast<ClickLbState>(!cur_state_);
    updateState(cur_state_ == kNormal ? normal_hover_ : selected_hover_);
    emit clicked();
  }
  QLabel::mousePressEvent(event);
}

void ClickedLabel::enterEvent(QEvent* event) {
  updateState(cur_state_ == kNormal ? normal_hover_ : selected_hover_);
  QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent* event) {
  updateState(cur_state_ == kNormal ? normal_ : selected_);
  QLabel::leaveEvent(event);
}

void ClickedLabel::setState(QString normal, QString hover, QString press,
    QString select, QString select_hover, QString select_press) {
  normal_ = normal;
  normal_hover_ = hover;
  normal_press_ = press;
  selected_ = select;
  selected_hover_ = select_hover;
  selected_press_ = select_press;

  setProperty("state", normal);
  repolish(this);
}

ClickLbState ClickedLabel::getCurSate() const {
  return cur_state_;
}


void ClickedLabel::updateState(const QString state) {
  setProperty("state", state);
  repolish(this);
  update();
}
