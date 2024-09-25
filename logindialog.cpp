#include "logindialog.h"

#include <fmt/format.h>

#include "httpmgr.h"
#include "qpushbutton.h"
#include "tcp_manager.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent),
                                            ui(new Ui::LoginDialog) {
  ui->setupUi(this);

  initHttpHandlers();

  connect(ui->register_btn, &QPushButton::clicked, this,
      &LoginDialog::switchRegister);
  connect(ui->forget_btn, &QPushButton::clicked, this,
      &LoginDialog::switchReset);

  connect(ui->login_btn, &QPushButton::clicked, this, [this] {
    const auto name = ui->user_lineEdit->text();
    if (name.isEmpty()) {
      showTip(tr("用户名不能为空"), false);
      return;
    }
    const auto password = ui->passwd_lineEdit->text();
    if (password.size() < 6 || password.size() > 15) {
      showTip(tr("密码长度应为6-15"), false);
      return;
    }
    enableBtn(false);

    nlohmann::json json;
    json["user"] = name.toStdString();
    json["passwd"] = password.toStdString();
    HttpMgr::GetInstance()->PostHttpRequest(
        QUrl(gate_url_prefix + "/user_login"), json, kIdLOGIN_USER, kLoginMod);
  });

  connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this,
      &LoginDialog::slot_login_mod_finished);

  connect(this, &LoginDialog::sig_connect_tcp, TcpManager::GetInstance().get(),
      &TcpManager::slot_tcp_connect);

  connect(TcpManager::GetInstance().get(), &TcpManager::sig_con_success,
      this, &LoginDialog::slot_tcp_con_finished);

  connect(TcpManager::GetInstance().get(), &TcpManager::sig_login_failed,
      this, &LoginDialog::slot_login_failed);
}

LoginDialog::~LoginDialog() {
  fmt::println("LoginDialog::~LoginDialog");
  delete ui;
}

void LoginDialog::slot_login_mod_finished(const ReqId id, const QString& res,
    const ErrorCode error_code) {
  if (error_code != ErrorCode::kSuccess) {
    showTip(tr("网络请求错误"), false);
    return;
  }

  nlohmann::json json = nlohmann::json::parse(res.toStdString());
  if (json.is_null()) {
    showTip(tr("json解析失败"), false);
    return;
  }

  if (json.empty()) {
    showTip(tr("json解析失败"), false);
    return;
  }

  handlers_[id](json);
}

void LoginDialog::slot_tcp_con_finished(const bool success) {
  if (!success) {
    fmt::print("网络异常\n");
    return;
  }
  showTip(tr("聊天服务器连接成功, 正在登录..."), true);
  nlohmann::json json;
  json["uid"] = server_info_.uid;
  json["token"] = server_info_.token.toStdString();

  emit TcpManager::GetInstance()->sig_send_data(ReqId::kIdCHAT_LOGIN,
      json.dump().c_str());
}

void LoginDialog::slot_login_failed(const int error_code) {
  showTip(QString("登录失败，错误码 %1").arg(error_code), false);
}

void LoginDialog::initHttpHandlers() {
  handlers_[kIdLOGIN_USER] = [this](nlohmann::json& json) {
    const int error_code = json["error"];
    if (error_code != ErrorCode::kSuccess) {
      showTip(tr("用户或密码错误"), false);
      return;
    }

    server_info_.host = QString::fromStdString(json["host"]);
    server_info_.port = QString::fromStdString(json["port"]);
    server_info_.token = QString::fromStdString(json["token"]);
    server_info_.uid = json["uid"];

    emit sig_connect_tcp(server_info_);
  };
}

void LoginDialog::showTip(const QString& text, const bool normal) {
  ui->error_label->setText(text);

  ui->error_label->setProperty("state", normal ? "normal" : "error");

  Repolish()(ui->error_label);

  if (!normal) {
    enableBtn(true);
  }
}

void LoginDialog::enableBtn(const bool enable) {
  ui->login_btn->setEnabled(enable);
  ui->forget_btn->setEnabled(enable);
}
