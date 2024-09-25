//
// Created by summer on 2024/9/24.
//

#ifndef CHAT_VIEW_H
#define CHAT_VIEW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>

class ChatView : public QWidget {
  Q_OBJECT

public:
  ChatView(QWidget* parent = nullptr);
  void appendChatItem(QWidget* item);
  void prependChatItem(QWidget* item);
  void insertChatItem(QWidget* before, QWidget* item);

protected:
  bool eventFilter(QObject* watched, QEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private slots:
  void onScrollBarMoved(int min, int max);

private:
  QVBoxLayout* verticalLayout_;
  QScrollArea* scrollArea_;
  QVBoxLayout* chatItemLayout_;
  bool append_ = false;
};


#endif //CHAT_VIEW_H
