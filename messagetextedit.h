//
// Created by summer on 2024/9/22.
//

#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include "global.h"
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QTextEdit>
#include <QVector>


class MessageTextEdit : public QTextEdit {
  Q_OBJECT

public:
  explicit MessageTextEdit(QWidget* parent = nullptr);

  ~MessageTextEdit();

  QVector<MsgInfo> getMsgList();

  void insertFileFromUrl(const QStringList& urls);
signals:
  void send();

protected:
  void dragEnterEvent(QDragEnterEvent* event);
  void dropEvent(QDropEvent* event);
  void keyPressEvent(QKeyEvent* e);

private:
  void insertImages(const QString& url);
  void insertTextFile(const QString& url);
  bool canInsertFromMimeData(const QMimeData* source) const;
  void insertFromMimeData(const QMimeData* source);

private:
  bool isImage(const QString& url); //判断文件是否为图片
  void insertMsgList(QVector<MsgInfo>& list, const QString& flag, const QString& text,
      const QPixmap& pix);

  QStringList getUrl(const QString& text);
  QPixmap getFileIconPixmap(const QString& url); //获取文件图标及大小信息，并转化成图片
  QString getFileSize(qint64 size); //获取文件大小

private slots:
  void textEditChanged();

private:
  QVector<MsgInfo> mMsgList;
  QVector<MsgInfo> mGetMsgList;
};

#endif // MESSAGETEXTEDIT_H
