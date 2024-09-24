//
// Created by summer on 2024/9/22.
//

#ifndef SEARCHLIST_H
#define SEARCHLIST_H

#include <QListWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class SearchList; }
QT_END_NAMESPACE

class SearchList : public QListWidget {
Q_OBJECT

public:
    explicit SearchList(QWidget *parent = nullptr);
    ~SearchList() override;

private:
};


#endif //SEARCHLIST_H
