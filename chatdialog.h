//
// Created by summer on 2024/9/19.
//

#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include "global.h"
#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui {
class ChatDialog;
}

QT_END_NAMESPACE

class ChatDialog : public QDialog {
  Q_OBJECT

public:
  explicit ChatDialog(QWidget* parent = nullptr);
  ~ChatDialog() override;

public slots:
  void slot_loading_chat_user();

private:
  void showSearch(bool search);
  void addChatUserList();

private:
  Ui::ChatDialog* ui;
  ChatUiMode mode_;
  ChatUiMode state_;
  bool loading_;
};


#endif //CHATDIALOG_H
