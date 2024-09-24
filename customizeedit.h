//
// Created by summer on 2024/9/22.
//

#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H

#include <QLineEdit>


class CustomizeEdit : public QLineEdit {
  Q_OBJECT

public:
  explicit CustomizeEdit(QWidget* parent = nullptr);
  ~CustomizeEdit() override;

  void setMaxLength(int maxLength);
signals:
  void sig_focus_out();

protected:
  void focusOutEvent(QFocusEvent* event) override;

private:
  void limitTextLength(const QString& text);

  int max_length_ = 0;
};


#endif //CUSTOMIZEEDIT_H
