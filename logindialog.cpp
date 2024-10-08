#include "logindialog.h"

#include <fmt/format.h>

#include "httpmgr.h"
#include "qpushbutton.h"
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
    auto name = ui->user_lineEdit->text();
    if (name.isEmpty()) {
      showTip(tr("用户名不能为空"), false);
      return;
    }
    auto password = ui->passwd_lineEdit->text();
    if (password.size() < 6 || password.size() > 15) {
      showTip(tr("密码长度应为6-15"), false);
      return;
    }

    nlohmann::json json;
    json["user"] = name.toStdString();
    json["passwd"] = password.toStdString();
    HttpMgr::GetInstance()->PostHttpRequest(
        QUrl(gate_url_prefix + "/user_login"), json, kIdLOGIN_USER, kLoginMod);
  });

  connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this,
      &LoginDialog::slot_login_mod_finished);
}

LoginDialog::~LoginDialog() {
  fmt::println("LoginDialog::~LoginDialog");
  delete ui;
}

void LoginDialog::slot_login_mod_finished(ReqId id, QString res,
    ErrorCode error_code) {
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

void LoginDialog::initHttpHandlers() {
  handlers_[kIdLOGIN_USER] = [this](nlohmann::json& json) {
    int error_code = json["error"];
    if (error_code != ErrorCode::kSuccess) {
      showTip(tr("用户或密码错误"), false);
      return;
    }

    showTip(tr("登录成功"), true);
  };
}

void LoginDialog::showTip(QString text, bool normal) {
  ui->error_label->setText(text);

  ui->error_label->setProperty("state", normal ? "normal" : "error");

  Repolish()(ui->error_label);
}
