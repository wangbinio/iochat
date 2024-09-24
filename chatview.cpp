//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatView.h" resolved

#include "chatview.h"
#include "ui_ChatView.h"


ChatView::ChatView(QWidget *parent) :
    QWidget(parent), ui(new Ui::ChatView) {
    ui->setupUi(this);
}

ChatView::~ChatView() {
    delete ui;
}
