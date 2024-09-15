//
// Created by summer on 2024/9/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ResetDialog.h" resolved

#include "resetdialog.h"

#include "httpmgr.h"
#include "ui_ResetDialog.h"


ResetDialog::ResetDialog(QWidget* parent) :
  QDialog(parent), ui(new Ui::ResetDialog) {
  ui->setupUi(this);

  initHttpHandlers();

  connect(ui->sure_btn, &QPushButton::clicked, [this] {
    nlohmann::json json;
    json["user"] = ui->user_lineEdit->text().toStdString();
    json["email"] = ui->email_lineEdit->text().toStdString();
    json["passwd"] = HashPassword(ui->newpasswd_lineEdit->text().toStdString());
    json["verifycode"] = ui->captcha_lineEdit->text().toStdString();
    HttpMgr::GetInstance()->PostHttpRequest(
        QUrl(gate_url_prefix + "/reset_passwd"), json, kIdRESET_PWD,
        kResetMod);
  });

  connect(ui->return_btn, &QPushButton::clicked, this,
      &ResetDialog::switchLogin);

  connect(ui->captcha_btn, &QPushButton::clicked, [this] {
    auto email = ui->email_lineEdit->text();
    static QRegularExpression regex(
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,}$)");
    auto match = regex.match(email).hasMatch();
    if (!match) {
      showTip(tr("邮箱地址不正确"), false);
      ui->captcha_btn->Stop();
      return;
    }

    // 发送验证码
    nlohmann::json json;
    json["email"] = email.toStdString();
    HttpMgr::GetInstance()->PostHttpRequest(
        QUrl(gate_url_prefix + "/get_verifycode"), json, kIdGetVerifyCode,
        kResetMod);
    showTip(tr("验证码已发送"), true);
  });

  connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reset_mod_finish, this,
      &ResetDialog::slot_reset_mod_finish);

  connect(ui->passwd_visible, &ClickedLabel::clicked, [this] {
    ui->newpasswd_lineEdit->setEchoMode(
        ui->passwd_visible->getCurSate() == kSelected
          ? QLineEdit::Normal
          : QLineEdit::Password);
  });

  showTip("", true);
}

ResetDialog::~ResetDialog() {
  fmt::print("ResetDialog::~ResetDialog\n");
  delete ui;
}

void ResetDialog::slot_reset_mod_finish(ReqId id, QString res,
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

void ResetDialog::showTip(QString text, bool normal) {
  ui->error_label->setText(text);

  ui->error_label->setProperty("state", normal ? "normal" : "error");

  Repolish()(ui->error_label);
}

void ResetDialog::initHttpHandlers() {
  handlers_.insert(ReqId::kIdGetVerifyCode, [this](const nlohmann::json& json) {
    int error_code = json["error"];
    if (error_code != ErrorCode::kSuccess) {
      showTip(tr("参数错误"), false);
      ui->captcha_btn->Stop();
      return;
    }

    std::string email = json["email"];
    std::string verify_code = json["verifycode"];
    ui->captcha_lineEdit->setText(QString::fromStdString(verify_code));
    showTip(tr("验证码已发送到邮箱"), true);
    fmt::print("email is {}\n", email);
    fmt::print(" verify_code is {}\n", verify_code);
  });

  handlers_[kIdRESET_PWD] = [this](const nlohmann::json& json) {
    int error_code = json["error"];
    if (error_code != ErrorCode::kSuccess) {
      showTip(tr("参数错误"), false);
      ui->captcha_btn->Stop();
      return;
    }

    showTip(tr("重置密码成功, 点击返回按钮登录"), true);
  };
}
