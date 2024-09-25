#include "./ui_mainwindow.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "qnamespace.h"
#include "registerdialog.h"
#include "tcp_manager.h"
#include <QLineEdit>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(TcpManager::GetInstance().get(), &TcpManager::sig_login_success,
      this, &MainWindow::showChatDialog);

  showLoginDialog();

  emit TcpManager::GetInstance()->sig_login_success();
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

void MainWindow::showChatDialog() {
  chat_dlg_ = new ChatDialog(this);
  chat_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  setCentralWidget(chat_dlg_);
  setMinimumSize({1200, 800});
  setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::clearLineEdit(const QWidget* widget) {
  auto lineEdits = widget->findChildren<QLineEdit*>();
  for (const auto line_edit : lineEdits) {
    line_edit->clear();
  }
}
