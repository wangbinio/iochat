//
// Created by summer on 2024/9/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatPage.h" resolved

#include "chatpage.h"
#include "ui_ChatPage.h"
#include <QPainter>
#include <QStyleOption>


ChatPage::ChatPage(QWidget* parent) :
  QWidget(parent), ui(new Ui::ChatPage) {
  ui->setupUi(this);
  setAttribute(Qt::WA_StyledBackground, true);
  ui->receive_btn->setState("normal", "hover", "press");
  ui->send_btn->setState("normal", "hover", "press");
  ui->emo_lb->setState("normal", "hover", "press", "normal", "hover", "press");
  ui->file_lb->setState("normal", "hover", "press", "normal", "hover", "press");
}

ChatPage::~ChatPage() {
  delete ui;
}

void ChatPage::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  QStyleOption option;
  option.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
