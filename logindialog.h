#pragma once

#include <QDialog>

#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

public:
  explicit LoginDialog(QWidget* parent = nullptr);
  ~LoginDialog();

public slots:
  void slot_login_mod_finished(ReqId id, QString res, ErrorCode error_code);
  void slot_tcp_con_finished(bool success);

signals:
  void switchRegister();
  void switchReset();
  void sig_connect_tcp(ServerInfo server_info);

private:
  Ui::LoginDialog* ui;
  ServerInfo server_info_;

  QMap<ReqId, std::function<void(nlohmann::json&)>> handlers_;
  void initHttpHandlers();
  void showTip(const QString&, bool);
};
