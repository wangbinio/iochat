//
// Created by summer on 2024/9/19.
//

#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include "global.h"
#include <QDialog>

#include "statewidget.h"

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
  void slot_side_chat();
  void slot_side_contact();

private:
  void initSideBar();
  void showSearch(bool search);
  void addChatUserList();
  void addLabelGroup(StateWidget* state_widget);
  void clearLabelState(const StateWidget* state_widget);

private:
  Ui::ChatDialog* ui;
  ChatUiMode mode_;
  ChatUiMode state_;
  bool loading_;
  QList<StateWidget*> state_widgets_;
};


#endif //CHATDIALOG_H
