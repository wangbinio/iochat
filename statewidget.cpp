//
// Created by summer on 2024/9/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StateWidget.h" resolved

#include "statewidget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>


StateWidget::StateWidget(QWidget* parent) :
  QWidget(parent), cur_state_(kNormal) {
  setCursor(Qt::PointingHandCursor);
  addRedPoint();
}

StateWidget::~StateWidget() {
}

void StateWidget::setState(const QString& normal, const QString& hover,
    const QString& press,
    const QString& select, const QString& select_hover,
    const QString& select_press) {
  normal_ = normal;
  normal_hover_ = hover;
  normal_press_ = press;
  selected_ = select;
  selected_hover_ = select_hover;
  selected_press_ = select_press;

  setProperty("state", normal);
  repolish(this);
}

ClickLbState StateWidget::getCurSate() const {
  return cur_state_;
}

void StateWidget::clearState() {
  cur_state_ = kNormal;
  updateState("normal");
}

void StateWidget::setSelected(const bool selected) {
  cur_state_ = selected ? kSelected : kNormal;
  updateState(selected ? selected_ : normal_);
}

void StateWidget::addRedPoint() {
  red_point_ = new QLabel(this);
  red_point_->setObjectName("red_point");
  red_point_->setAlignment(Qt::AlignCenter);
  red_point_->setVisible(false);

  auto layout = new QVBoxLayout(this);
  layout->setMargin(0);
  layout->addWidget(red_point_);
  setLayout(layout);
}

void StateWidget::showRedPoint(const bool show) {
  red_point_->setVisible(show);
}

void StateWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    cur_state_ = static_cast<ClickLbState>(!cur_state_);
    updateState(cur_state_ == kNormal ? normal_press_ : selected_press_);
    return;
  }
  QWidget::mousePressEvent(event);
}

void StateWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    // cur_state_ = static_cast<ClickLbState>(!cur_state_);
    updateState(cur_state_ == kNormal ? normal_hover_ : selected_hover_);
    emit clicked();
    return;
  }
  QWidget::mouseReleaseEvent(event);
}

void StateWidget::enterEvent(QEvent* event) {
  updateState(cur_state_ == kNormal ? normal_hover_ : selected_hover_);
  QWidget::enterEvent(event);
}

void StateWidget::leaveEvent(QEvent* event) {
  updateState(cur_state_ == kNormal ? normal_ : selected_);
  QWidget::leaveEvent(event);
}

void StateWidget::paintEvent(QPaintEvent* event) {
  QStyleOption option;
  option.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void StateWidget::updateState(const QString& state) {
  setProperty("state", state);
  repolish(this);
  update();
}
