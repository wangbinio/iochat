//
// Created by summer on 2024/9/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatPage.h" resolved

#include "chatpage.h"
#include "ui_ChatPage.h"
#include <QPainter>
#include <QStyleOption>

#include "chat_item_base.h"
#include "picture_bubble.h"
#include "text_bubble.h"


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

void ChatPage::on_send_btn_clicked() {
  auto text_edit = ui->chatEdit;
  ChatRole role = ChatRole::kSelf;
  const QString user_name("loktar");
  const QString user_icon(":/res/head_1.jpg");
  const auto& msg_list = text_edit->getMsgList();
  for (int i = 0; i < msg_list.size(); ++i) {
    auto type = msg_list.at(i).msgFlag;
    auto chat_item = new ChatItemBase(role);
    chat_item->setUserName(user_name);
    chat_item->setUserIcon(user_icon);
    QWidget* bubble = nullptr;
    if (type == "text") {
      bubble = new TextBubble(role, msg_list.at(i).content);
    } else if (type == "image") {
      bubble = new PictureBubble(role, msg_list.at(i).content);
    } else if (type == "file") {
      ;
    }
    if (bubble) {
      chat_item->setWidget(bubble);
      ui->chat_data_list->appendChatItem(chat_item);
    }
  }
}
