#include "httpmgr.h"

HttpMgr::HttpMgr() {
  connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpRequest(const QUrl& url, const nlohmann::json& json,
    ReqId req_id, Modules mod) {
  const QByteArray data(json.dump().data());
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setHeader(QNetworkRequest::ContentLengthHeader,
      QByteArray::number(data.length()));

  auto self = shared_from_this();
  QNetworkReply* reply = manager_.post(request, data);
  connect(reply, &QNetworkReply::finished, [this, self, reply, req_id, mod]() {
    if (reply->error() != QNetworkReply::NoError) {
      fmt::print("{}\n", reply->errorString().toStdString());
      emit sig_http_finish(req_id, "", ErrorCode::kErrorNetwork, mod);
      reply->deleteLater();
      return;
    }

    const QString res = reply->readAll();
    emit sig_http_finish(req_id, res, ErrorCode::kSuccess, mod);
    reply->deleteLater();
    return;
  });
}

void HttpMgr::slot_http_finish(const ReqId id, const QString& res, const ErrorCode error_code,
    const Modules mod) {
  if (mod == Modules::kRegisterMod) {
    emit sig_reg_mod_finish(id, res, error_code);
  } else if (mod == kResetMod) {
    emit sig_reset_mod_finish(id, res, error_code);
  } else if (mod == kLoginMod) {
    emit sig_login_mod_finish(id, res, error_code);
  }
}

HttpMgr::~HttpMgr() {
}
