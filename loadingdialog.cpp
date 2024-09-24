//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoadingDialog.h" resolved

#include "loadingdialog.h"
#include "ui_LoadingDialog.h"
#include <QMovie>

LoadingDialog::LoadingDialog(QWidget* parent) :
  QDialog(parent), ui(new Ui::LoadingDialog) {
  ui->setupUi(this);

  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
                 | Qt::WindowSystemMenuHint);
  setAttribute(Qt::WA_TranslucentBackground);

  setFixedSize(parent->size());

  const auto movie = new QMovie(":/res/loading.git");
  ui->loading_lb->setMovie(movie);
  movie->start();
}

LoadingDialog::~LoadingDialog() {
  delete ui;
}
