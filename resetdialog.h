//
// Created by summer on 2024/9/12.
//

#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>

#include "global.h"


QT_BEGIN_NAMESPACE

namespace Ui {
class ResetDialog;
}

QT_END_NAMESPACE

class ResetDialog : public QDialog {
  Q_OBJECT

public:
  explicit ResetDialog(QWidget* parent = nullptr);

  ~ResetDialog() override;

public slots:
  void slot_reset_mod_finish(ReqId id, const QString& res, ErrorCode error_code);
signals:
  void switchLogin();

private:
  void showTip(const QString&, bool);
  void initHttpHandlers();

  Ui::ResetDialog* ui;
  QMap<ReqId, std::function<void(nlohmann::json&)>> handlers_;
};


#endif //RESETDIALOG_H
