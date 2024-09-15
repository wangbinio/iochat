#pragma once

#include <QMainWindow>

#include "resetdialog.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class LoginDialog;
class RegisterDialog;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void showLoginDialog();
  void showRegisterDialog();
  void showResetDialog();
  static void clearLineEdit(const QWidget* widget);

private:
  Ui::MainWindow* ui;
  LoginDialog* login_dlg_;
  RegisterDialog* register_dlg_;
  ResetDialog* reset_dlg_;
};
