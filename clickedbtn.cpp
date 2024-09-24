//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ClickedBtn.h" resolved

#include "clickedbtn.h"
#include "ui_ClickedBtn.h"
#include "global.h"

ClickedBtn::ClickedBtn(QWidget* parent) :
  QPushButton(parent) {
  setCursor(Qt::PointingHandCursor);
  setState("normal", "hover", "press");
}

ClickedBtn::~ClickedBtn() {
}

void ClickedBtn::setState(QString normal, QString hover, QString press) {
  normal_ = normal;
  hover_ = hover;
  press_ = press;
  setProperty("state", normal);
  repolish(this);
}

void ClickedBtn::enterEvent(QEvent* event) {
  updateState(hover_);
  QPushButton::enterEvent(event);
}

void ClickedBtn::leaveEvent(QEvent* event) {
  updateState(normal_);
  QPushButton::leaveEvent(event);
}

void ClickedBtn::mousePressEvent(QMouseEvent* event) {
  updateState(press_);
  QPushButton::mousePressEvent(event);
}

void ClickedBtn::mouseReleaseEvent(QMouseEvent* event) {
  updateState(hover_);
  QPushButton::mouseReleaseEvent(event);
}

void ClickedBtn::updateState(QString state) {
  setProperty("state", state);
  repolish(this);
  update();
}
