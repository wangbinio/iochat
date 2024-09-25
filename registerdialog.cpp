#include "registerdialog.h"

#include <QLabel>
#include <QLineEdit>

#include "global.h"
#include "httpmgr.h"
#include "qlineedit.h"
#include "qregularexpression.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget* parent) : QDialog(parent),
                                                  ui(new Ui::RegisterDialog),
                                                  countdown_(5) {
  ui->setupUi(this);
  ui->passwd_lineEdit->setEchoMode(QLineEdit::Password);
  ui->passwd_comfirm_lineEdit->setEchoMode(QLineEdit::Password);
  ui->error_label->setProperty("state", "normal");
  ui->confirm_visible->setState("unvisible", "unvisible_hover", "", "visible",
      "visible_hover", "");
  ui->passwd_visible->setState("unvisible", "unvisible_hover", "", "visible",
      "visible_hover", "");
  Repolish()(ui->error_label);
  ui->error_label->clear();

  initInputErrorCheck();

  initHttpHandlers();
  connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this,
      &RegisterDialog::slot_reg_mod_finish);

  connect(ui->passwd_visible, &ClickedLabel::clicked, this, [this] {
    ui->passwd_lineEdit->setEchoMode(
        ui->passwd_visible->getCurSate() == ClickLbState::kSelected
          ? QLineEdit::Normal
          : QLineEdit::Password);
  });
  connect(ui->confirm_visible, &ClickedLabel::clicked, this, [this] {
    ui->passwd_comfirm_lineEdit->setEchoMode(
        ui->confirm_visible->getCurSate() == ClickLbState::kSelected
          ? QLineEdit::Normal
          : QLineEdit::Password);
  });

  countdown_timer_ = new QTimer(this);
  connect(countdown_timer_, &QTimer::timeout, this, [this] {
    if (--countdown_ == 0) {
      stopCountdownTimer();
      emit switchLogin();
      return;
    }
    ui->label_success->setText(QString("注册成功，%1s后返回登录").arg(countdown_));
  });

  connect(ui->return_btn, &QPushButton::clicked, this, [this] {
    stopCountdownTimer();
    emit switchLogin();
  });
  connect(ui->cancel_btn, &QPushButton::clicked, this, [this] {
    stopCountdownTimer();
    emit switchLogin();
  });
}

RegisterDialog::~RegisterDialog() {
  fmt::println("RegisterDialog::~RegisterDialog");
  delete ui;
}

void RegisterDialog::on_captcha_btn_clicked() {
  const auto email = ui->email_lineEdit->text();
  static QRegularExpression regex(
      R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,}$)");
  const auto match = regex.match(email).hasMatch();
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
      kRegisterMod);
  showTip(tr("验证码已发送"), true);
}

void RegisterDialog::on_sure_btn_clicked() {
  if (!tip_err_.empty()) {
    showTip(tr("输入有误"), false);
    return;
  }

  nlohmann::json json;
  json["user"] = ui->user_lineEdit->text().toStdString();
  json["email"] = ui->email_lineEdit->text().toStdString();
  json["passwd"] = HashPassword(ui->passwd_lineEdit->text().toStdString());
  json["confirm"] = json["passwd"];
  json["verifycode"] = ui->captcha_lineEdit->text().toStdString();
  HttpMgr::GetInstance()->PostHttpRequest(
      QUrl(gate_url_prefix + "/user_register"), json, kIdRegUser, kRegisterMod);
}

void RegisterDialog::slot_reg_mod_finish(const ReqId id, const QString& res,
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

void RegisterDialog::showTip(const QString& text, const bool normal) {
  ui->error_label->setText(text);

  ui->error_label->setProperty("state", normal ? "normal" : "error");

  Repolish()(ui->error_label);
}

void RegisterDialog::initHttpHandlers() {
  handlers_.insert(ReqId::kIdGetVerifyCode, [this](const nlohmann::json& json) {
    const int error_code = json["error"];
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

  handlers_.insert(ReqId::kIdRegUser, [this](const nlohmann::json& json) {
    const int error_code = json["error"];
    if (error_code != ErrorCode::kSuccess) {
      if (error_code == ErrorCode::kVerifyCodeErr) {
        showTip(tr("验证码错误"), false);
      } else if (error_code == ErrorCode::kVerifyExpired) {
        showTip(tr("验证码过期"), false);
      } else {
        showTip(tr("参数错误"), false);
      }
      return;
    }

    std::string_view email = json["email"];
    showTip(tr("用户注册成功"), true);
    fmt::print("email is {}\n", email);

    changeToTipPage();
  });
}

void RegisterDialog::initInputErrorCheck() {
  connect(ui->user_lineEdit, &QLineEdit::editingFinished, this, [this] {
    if (ui->user_lineEdit->text().isEmpty()) {
      addTip(kTipUserErr, tr("用户名不能为空"));
      return;
    }
    delTip(kTipUserErr);
  });

  connect(ui->passwd_lineEdit, &QLineEdit::editingFinished, this, [this] {
    const auto passwd = ui->passwd_lineEdit->text();
    if (passwd.size() > 15 || passwd.size() < 6) {
      addTip(kTipPwdErr, tr("密码长度为6-15"));
      return;
    }

    // 密码检测正则表达式, 允许数字，字母，下划线和部分特殊字符
    static QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    if (!regExp.match(passwd).hasMatch()) {
      addTip(kTipPwdErr, tr("密码格式错误"));
      return;
    }

    delTip(kTipPwdErr);
  });

  connect(ui->email_lineEdit, &QLineEdit::editingFinished, this, [this] {
    const auto email = ui->email_lineEdit->text();
    if (email.isEmpty()) {
      addTip(kTipEmailErr, tr("邮箱不能为空"));
      return;
    }

    // 邮箱检测正则表达式
    static QRegularExpression regExp(
        "^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
    if (!regExp.match(email).hasMatch()) {
      addTip(kTipEmailErr, tr("邮箱格式错误"));
      return;
    }

    delTip(kTipEmailErr);
  });

  connect(ui->captcha_lineEdit, &QLineEdit::editingFinished, this, [this] {
    if (ui->captcha_lineEdit->text().isEmpty()) {
      addTip(kTipVerifyErr, tr("验证码不能为空"));
      return;
    }
    delTip(kTipVerifyErr);
  });
}

void RegisterDialog::addTip(const TipErr tip_err, const QString& error) {
  tip_err_[tip_err] = error;
  showTip(error, false);
}

void RegisterDialog::delTip(const TipErr tip_err) {
  tip_err_.remove(tip_err);
  if (tip_err_.empty()) {
    ui->error_label->clear();
  } else {
    showTip(tip_err_.first(), false);
  }
}

void RegisterDialog::stopCountdownTimer() {
  countdown_timer_->stop();
  countdown_ = 5;
}

void RegisterDialog::changeToTipPage() {
  stopCountdownTimer();
  countdown_timer_->start(1000);
  ui->stackedWidget->setCurrentWidget(ui->page_2);
}
