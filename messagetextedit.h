//
// Created by summer on 2024/9/22.
//

#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include <QTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MessageTextEdit; }
QT_END_NAMESPACE

class MessageTextEdit : public QTextEdit {
Q_OBJECT

public:
    explicit MessageTextEdit(QWidget *parent = nullptr);
    ~MessageTextEdit() override;

private:
};


#endif //MESSAGETEXTEDIT_H
