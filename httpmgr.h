#pragma once

#include "singleton.h"

class HttpMgr : public QObject, public Singleton<HttpMgr>,
                public std::enable_shared_from_this<HttpMgr> {
  Q_OBJECT
  friend class Singleton<HttpMgr>;

public:
  ~HttpMgr() override;

  void PostHttpRequest(QUrl url, const nlohmann::json& json, ReqId req_id,
      Modules mod);

private:
  HttpMgr();
  QNetworkAccessManager manager_;

private slots:
  void slot_http_finish(ReqId id, QString res, ErrorCode error_code,
      Modules mod);
signals:
  void sig_http_finish(ReqId id, QString res, ErrorCode error_code,
      Modules mod);
  void sig_reg_mod_finish(ReqId id, QString res, ErrorCode error_code);
  void sig_reset_mod_finish(ReqId id, QString res, ErrorCode error_code);
  void sig_login_mod_finish(ReqId id, QString res, ErrorCode error_code);
};
