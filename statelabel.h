//
// Created by summer on 2024/9/22.
//

#ifndef STATELABEL_H
#define STATELABEL_H

#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class StateLabel; }
QT_END_NAMESPACE

class StateLabel : public QLabel {
Q_OBJECT

public:
    explicit StateLabel(QWidget *parent = nullptr);
    ~StateLabel() override;

private:
    Ui::StateLabel *ui;
};


#endif //STATELABEL_H
