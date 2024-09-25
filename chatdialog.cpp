//
// Created by summer on 2024/9/19.
//
#include "chatdialog.h"
#include "chatuserwidget.h"
#include "loadingdialog.h"
#include "ui_ChatDialog.h"
#include <QAction>
#include <QRandomGenerator>

std::vector<QString> messages = {
    "hello world !",
    "nice to meet u",
    "New year，new life",
    "You have to love yourself",
    "My love is written in the wind ever since the whole world is you"};

std::vector<QString> heads = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};

std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

ChatDialog::ChatDialog(QWidget* parent) :
  QDialog(parent), ui(new Ui::ChatDialog), mode_(kChatMode), state_(kChatMode),
  loading_(false) {
  ui->setupUi(this);
  ui->search_edit->setMaxLength(20);

  QAction* search_action = new QAction(ui->search_edit);
  search_action->setIcon(QIcon{":/res/search.png"});
  ui->search_edit->addAction(search_action, QLineEdit::LeadingPosition);
  ui->search_edit->setPlaceholderText(QStringLiteral("搜索"));

  QAction* clear_action = new QAction(ui->search_edit);
  clear_action->setIcon(QIcon{":/res/close_transparent.png"});
  ui->search_edit->addAction(clear_action, QLineEdit::TrailingPosition);
  connect(ui->search_edit, &QLineEdit::textChanged, [clear_action, this](const
      QString& text) {
        if (text.isEmpty()) {
          clear_action->setIcon(QIcon{":/res/close_transparent.png"});
        } else {
          clear_action->setIcon(QIcon{":/res/close_search.png"});
          showSearch(true);
        }
      });
  connect(clear_action, &QAction::triggered, [this, clear_action]() {
    ui->search_edit->clear();
    ui->search_edit->clearFocus();
    clear_action->setIcon(QIcon{":/res/close_transparent.png"});
    showSearch(false);
  });

  connect(ui->chat_user_list, &ChatUserList::sig_loading_chat_user, this,
      &ChatDialog::slot_loading_chat_user);

  addChatUserList();

  showSearch(false);

  initSideBar();
}

ChatDialog::~ChatDialog() {
}

void ChatDialog::slot_loading_chat_user() {
  if (loading_) return;

  loading_ = true;
  LoadingDialog loading_dialog(this);
  loading_dialog.setModal(true);
  loading_dialog.show();
  fmt::print("Loading user list...\n");
  addChatUserList();
  loading_ = false;
}

void ChatDialog::slot_side_chat() {
  clearLabelState(ui->side_chat_lb);
  ui->stackedWidget->setCurrentWidget(ui->chat_page);
  state_ = ChatUiMode::kChatMode;
  showSearch(false);
}

void ChatDialog::slot_side_contact() {
  clearLabelState(ui->side_contact_lb);
  ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
  state_ = ChatUiMode::kContactMode;
  showSearch(false);
}

void ChatDialog::initSideBar() {
  QPixmap pixmap(":/res/head_1.jpg");
  pixmap = pixmap.scaled(ui->side_head_lb->size(), Qt::KeepAspectRatio);
  ui->side_head_lb->setPixmap(pixmap);
  ui->side_head_lb->setScaledContents(true);

  ui->side_chat_lb->setState("normal", "hover", "pressed", "selected_normal",
      "selected_hover", "selected_pressed");
  ui->side_chat_lb->setProperty("state", "selected_normal");
  ui->side_contact_lb->setState("normal", "hover", "pressed", "selected_normal",
      "selected_hover", "selected_pressed");

  addLabelGroup(ui->side_chat_lb);
  addLabelGroup(ui->side_contact_lb);

  connect(ui->side_chat_lb, &StateWidget::clicked, this,
      &ChatDialog::slot_side_chat);
  connect(ui->side_contact_lb, &StateWidget::clicked, this,
      &ChatDialog::slot_side_contact);
}

void ChatDialog::showSearch(const bool search) {
  if (search) {
    ui->chat_user_list->hide();
    ui->con_user_list->hide();
    ui->search_list->show();
    mode_ = ChatUiMode::kSearchMode;
  } else if (state_ == ChatUiMode::kChatMode) {
    ui->chat_user_list->show();
    ui->con_user_list->hide();
    ui->search_list->hide();
    mode_ = ChatUiMode::kChatMode;
  } else if (state_ == ChatUiMode::kContactMode) {
    ui->chat_user_list->hide();
    ui->con_user_list->show();
    ui->search_list->hide();
    mode_ = ChatUiMode::kContactMode;
  }
}

void ChatDialog::addChatUserList() {
  static int index = 0;
  for (int i = 0; i < 13; ++i) {
    const auto value = QRandomGenerator::global()->bounded(100);
    const auto head_index = value % heads.size();
    const auto name_index = value % names.size();
    const auto message_index = value % messages.size();

    const auto chat_user_wid = new ChatUserWidget();
    chat_user_wid->setInfo(QString(names[name_index]).append(QString::number
            (++index)),
        heads[head_index],
        messages[message_index]);
    const auto item = new QListWidgetItem();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chat_user_list->addItem(item);
    ui->chat_user_list->setItemWidget(item, chat_user_wid);
  }
}

void ChatDialog::addLabelGroup(StateWidget* state_widget) {
  state_widgets_.append(state_widget);
}

void ChatDialog::clearLabelState(const StateWidget* state_widget) {
  for (const auto& w : state_widgets_) {
    if (w == state_widget) continue;
    w->clearState();
  }
}
