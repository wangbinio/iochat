//
// Created by summer on 2024/9/23.
//

#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
class ChatPage;
}

QT_END_NAMESPACE

class ChatPage : public QWidget {
  Q_OBJECT

public:
  explicit ChatPage(QWidget* parent = nullptr);
  ~ChatPage() override;
  void paintEvent(QPaintEvent* event) override;

public slots:
  void on_send_btn_clicked();

private:
  Ui::ChatPage* ui;
};


#endif //CHATPAGE_H
