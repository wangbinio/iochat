//
// Created by summer on 2024/9/16.
//

#ifndef TCP_MANAGER_H
#define TCP_MANAGER_H
#include <QTcpSocket>
#include "singleton.h"
#include "global.h"


class TcpManager : public QObject, public Singleton<TcpManager>,
                   public std::enable_shared_from_this<TcpManager> {
  friend class Singleton<TcpManager>;
  Q_OBJECT

public:
  ~TcpManager();

public slots:
  void slot_tcp_connect(const ServerInfo& server_info);
  void slot_send_data(ReqId req_id, const QByteArray& data);

signals:
  void sig_send_data(ReqId req_id, QByteArray data);
  void sig_con_success(bool success);
  void sig_login_failed(int error_code);
  void sig_login_success();

private:
  TcpManager();
  void InitHandlers();
  void HandleMessage(ReqId req_id, int len, const QByteArray& data);

  QTcpSocket socket_;
  QString host_;
  uint16_t port_ = 0;
  uint16_t message_id_ = 0;
  uint16_t message_len_ = 0;
  QDataStream in_;
  QDataStream out_;
  QByteArray buffer_;
  bool recv_padding_ = false;
  QMap<ReqId, std::function<void(ReqId, int, QByteArray)>> handlers_;
};


#endif //TCP_MANAGER_H
