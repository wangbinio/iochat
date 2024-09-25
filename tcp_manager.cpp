//
// Created by summer on 2024/9/16.
//

#include "tcp_manager.h"
#include "user_manager.h"
#include <QBuffer>

TcpManager::TcpManager() {
  in_.setDevice(&socket_);
  in_.setVersion(QDataStream::Qt_5_15);
  in_.setByteOrder(QDataStream::BigEndian);

  out_.setVersion(QDataStream::Qt_5_15);
  out_.setByteOrder(QDataStream::BigEndian);

  InitHandlers();

  connect(this, &TcpManager::sig_send_data, this, &TcpManager::slot_send_data);

  connect(&socket_, &QTcpSocket::connected, [this] {
    fmt::println("Connected");
    emit sig_con_success(true);
  });

  connect(&socket_, &QTcpSocket::disconnected, [this] {
    fmt::println("Disconnected");
  });

  connect(&socket_, &QTcpSocket::errorOccurred,
      [this](QTcpSocket::SocketError) {
        fmt::println("Socket error:{}", socket_.errorString().toStdString());
      });

  connect(&socket_, &QTcpSocket::readyRead, [this] {
    while (socket_.bytesAvailable() > 0) {
      in_.startTransaction();
      in_ >> message_id_ >> message_len_;
      if (socket_.bytesAvailable() < message_len_) {
        in_.rollbackTransaction();
        return;
      }
      buffer_.resize(message_len_);
      // in_ >> buffer_;
      in_.readRawData(buffer_.data(), message_len_);
      if (!in_.commitTransaction()) {
        return;
      }
      HandleMessage(static_cast<ReqId>(message_id_), message_len_, buffer_);
    }
  });
}

TcpManager::~TcpManager() {
}

void TcpManager::slot_tcp_connect(const ServerInfo& server_info) {
  fmt::print("TcpManager::slot_tcp_connect\n");
  fmt::print("Connecting to server {}:{}\n", server_info.host.toStdString(),
      server_info.port.toStdString());
  host_ = server_info.host;
  port_ = static_cast<uint16_t>(server_info.port.toUInt());
  socket_.connectToHost(host_, port_);
}

void TcpManager::slot_send_data(const ReqId req_id, const QByteArray& data) {
  const auto id = static_cast<uint16_t>(req_id);
  const auto len = static_cast<uint16_t>(data.length());

  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  out_.setDevice(&buffer);
  out_ << id << len;
  // out_ << data;
  buffer.buffer().append(data);
  fmt::println("send buf: {}", data.toStdString());
  socket_.write(buffer.buffer());
}

void TcpManager::InitHandlers() {
  handlers_[kIdCHAT_LOGIN_RSP] = [this](const ReqId req_id, int len, const QByteArray&
      data) {
        if (req_id != kIdCHAT_LOGIN_RSP) {
          fmt::print("Error: kIdCHAT_LOGIN_RSP recv {}\n",
              static_cast<int>(req_id));
          emit sig_login_failed(kErrorJson);
          return;
        }
        try {
          nlohmann::json json = nlohmann::json::parse(data);
          const auto error_code = json["error"].get<int>();
          if (error_code != kSuccess) {
            fmt::print("Login Error {}\n", error_code);
            emit sig_login_failed(kErrorJson);
            return;
          }
          UserManager::GetInstance()->SetUser(json["id"].get<int>(),
              json["name"].get<std::string>().data(),
              json["token"].get<std::string>().data());

          fmt::print("Login Success\n");
          emit sig_login_success();
        } catch (std::exception& exception) {
          fmt::print("Login Error {}\n", exception.what());
          emit sig_login_failed(kErrorJson);
        }
      };
}

void TcpManager::HandleMessage(const ReqId req_id, const int len,
    const QByteArray& data) {
  const auto iter = handlers_.find(req_id);
  if (iter == handlers_.end()) {
    fmt::println("Handler {} not found", static_cast<int>(req_id));
    return;
  }

  iter.value()(req_id, len, data);
}
