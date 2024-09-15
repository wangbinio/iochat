#pragma once

#include <QFile>
#include <QDir>
#include <QString>
#include <QSettings>
#include <QByteArray>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStyle>
#include <QUrl>
#include <QWidget>
#include <chrono>
#include <fmt/core.h>
#include <fmt/format.h>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <thread>
#include <typeinfo>

extern std::function<void(QWidget*)> repolish;

extern QString gate_url_prefix;

inline auto Repolish() {
  return [](QWidget* w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
  };
}

std::string HashPassword(const std::string& password);

bool CheckPassword(const std::string& password, const std::string& hash);

enum ReqId {
  kIdGetVerifyCode = 1001, // 获取验证码
  kIdRegUser = 1002, //     ID_RESET_PWD = 1003, //重置密码
  kIdRESET_PWD = 1003, //重置密码
  kIdLOGIN_USER = 1004, //用户登录
  kIdCHAT_LOGIN = 1005, //登陆聊天服务器
  kIdCHAT_LOGIN_RSP = 1006, //登陆聊天服务器回包
  kIdSEARCH_USER_REQ = 1007, //用户搜索请求
  kIdSEARCH_USER_RSP = 1008, //搜索用户回包
  kIdADD_FRIEND_REQ = 1009, //添加好友申请
  kIdADD_FRIEND_RSP = 1010, //申请添加好友回复
  kIdNOTIFY_ADD_FRIEND_REQ = 1011, //通知用户添加好友申请
  kIdAUTH_FRIEND_REQ = 1013, //认证好友请求
  kIdAUTH_FRIEND_RSP = 1014, //认证好友回复
  kIdNOTIFY_AUTH_FRIEND_REQ = 1015, //通知用户认证好友申请
  kIdTEXT_CHAT_MSG_REQ = 1017, //文本聊天信息请求
  kIdTEXT_CHAT_MSG_RSP = 1018, //文本聊天信息回复
  kIdNOTIFY_TEXT_CHAT_MSG_REQ = 1019, //通知用户文本聊天信息
};

enum Modules {
  kRegisterMod = 0,
  kResetMod = 1,
  kLoginMod = 2,
};

enum ErrorCode {
  kSuccess = 0,
  kErrorJson = 1, //Json解析错误
  kErrorNetwork = 2, //网络错误
  kRPCFailed = 1002, //RPC请求错误
  kVerifyExpired = 1003, //验证码过期
  kVerifyCodeErr = 1004, //验证码错误
  kUserExist = 1005, //用户已经存在
  kPasswdErr = 1006, //密码错误
  kEmailNotMatch = 1007, //邮箱不匹配
  kPasswdUpFailed = 1008, //更新密码失败
  kPasswdInvalid = 1009, //密码更新失败
  kTokenInvalid = 1010, //Token失效
  kUidInvalid = 1011, //uid无效
};

enum TipErr {
  kTipSuccess = 0,
  kTipEmailErr = 1,
  kTipPwdErr = 2,
  kTipConfirmErr = 3,
  kTipPwdConfirmErr = 4,
  kTipVerifyErr = 5,
  kTipUserErr = 6
};

enum ClickLbState {
  kNormal = 0,
  kSelected = 1
};
