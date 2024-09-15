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

signals:
  void switchRegister();
  void switchReset();

private:
  Ui::LoginDialog* ui;

  QMap<ReqId, std::function<void(nlohmann::json&)>> handlers_;
  void initHttpHandlers();
  void showTip(QString, bool);
};
