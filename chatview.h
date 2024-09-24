//
// Created by summer on 2024/9/22.
//

#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ChatView; }
QT_END_NAMESPACE

class ChatView : public QWidget {
Q_OBJECT

public:
    explicit ChatView(QWidget *parent = nullptr);
    ~ChatView() override;

private:
    Ui::ChatView *ui;
};


#endif //CHATVIEW_H
