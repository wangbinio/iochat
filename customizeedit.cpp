//
// Created by summer on 2024/9/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CustomizeEdit.h" resolved

#include "customizeedit.h"
#include "ui_CustomizeEdit.h"


CustomizeEdit::CustomizeEdit(QWidget* parent) :
  QLineEdit(parent) {
  connect(this, &QLineEdit::textChanged, this, &CustomizeEdit::limitTextLength);
}

CustomizeEdit::~CustomizeEdit() {
}

void CustomizeEdit::setMaxLength(int maxLength) {
  max_length_ = maxLength;
}

void CustomizeEdit::focusOutEvent(QFocusEvent* event) {
  QLineEdit::focusOutEvent(event);
  emit sig_focus_out();
}

void CustomizeEdit::limitTextLength(const QString& text) {
  if (max_length_ <= 0) return;

  QByteArray byte_array = text.toUtf8();

  if (byte_array.length() > max_length_) {
    setText(byte_array.left(max_length_));
  }
}
