#include "mainwindow.h"

#include <QLineEdit>
#include <QStackedWidget>

#include "./ui_mainwindow.h"
#include "logindialog.h"


#include "qnamespace.h"
#include "registerdialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
  ui->setupUi(this);

  showLoginDialog();
}

void MainWindow::showLoginDialog() {
  login_dlg_ = new LoginDialog(this);
  login_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  connect(login_dlg_, &LoginDialog::switchRegister, this,
      &MainWindow::showRegisterDialog);
  connect(login_dlg_, &LoginDialog::switchReset, this,
      &MainWindow::showResetDialog);
  setCentralWidget(login_dlg_);
}

void MainWindow::showRegisterDialog() {
  register_dlg_ = new RegisterDialog(this);
  register_dlg_->setWindowFlags(
      Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  connect(register_dlg_, &RegisterDialog::switchLogin, this,
      &MainWindow::showLoginDialog);
  setCentralWidget(register_dlg_);
}

void MainWindow::showResetDialog() {
  reset_dlg_ = new ResetDialog(this);
  reset_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  connect(reset_dlg_, &ResetDialog::switchLogin, this,
      &MainWindow::showLoginDialog);
  setCentralWidget(reset_dlg_);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::clearLineEdit(const QWidget* widget) {
  auto lineEdits = widget->findChildren<QLineEdit*>();
  for (const auto line_edit : lineEdits) {
    line_edit->clear();
  }
}
