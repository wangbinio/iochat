#pragma once

#include <QDialog>

#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog {
  Q_OBJECT

public:
  explicit RegisterDialog(QWidget* parent = nullptr);
  ~RegisterDialog() override;

private slots:
  void on_captcha_btn_clicked();
  void on_sure_btn_clicked();
  void slot_reg_mod_finish(ReqId id, QString res, ErrorCode error_code);

signals:
  void switchLogin();

private:
  void showTip(QString, bool);
  void initHttpHandlers();
  void initInputErrorCheck();
  void addTip(TipErr tip_err, QString error);
  void delTip(TipErr tip_err);
  void stopCountdownTimer();

  void changeToTipPage();

  Ui::RegisterDialog* ui;

  QMap<ReqId, std::function<void(nlohmann::json&)>> handlers_;
  QMap<TipErr, QString> tip_err_;

  QTimer* countdown_timer_;
  int countdown_;
};
