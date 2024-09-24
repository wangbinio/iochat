//
// Created by summer on 2024/9/22.
//

#ifndef CHATUSERWIDGET_H
#define CHATUSERWIDGET_H

#include "list_item_base.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class ChatUserWidget;
}

QT_END_NAMESPACE

class ChatUserWidget : public ListItemBase {
  Q_OBJECT

public:
  explicit ChatUserWidget(QWidget* parent = nullptr);
  ~ChatUserWidget() override;

  QSize sizeHint() const override;

  void setInfo(const QString& name, const QString& head,
      const QString& message);

private:
  Ui::ChatUserWidget* ui;
  QString name_;
  QString head_;
  QString message_;
};


#endif //CHATUSERWIDGET_H
