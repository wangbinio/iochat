//
// Created by summer on 2024/9/22.
//

#ifndef CHATUSERLIST_H
#define CHATUSERLIST_H

#include <QListWidget>

class ChatUserList : public QListWidget {
  Q_OBJECT

public:
  explicit ChatUserList(QWidget* parent = nullptr);
  ~ChatUserList() override;
signals:
  void sig_loading_chat_user();

protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

private:
};


#endif //CHATUSERLIST_H
