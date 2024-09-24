//
// Created by summer on 2024/9/20.
//

#include "user_manager.h"

UserManager::~UserManager() {
}

void UserManager::SetUid(const int uid) {
  uid_ = uid;
}

void UserManager::SetName(const QString& name) {
  name_ = name;
}

void UserManager::SetToken(const QString& token) {
  token_ = token;
}

void UserManager::SetUser(const int uid, const QString& name,
    const QString& token) {
  uid_ = uid;
  name_ = name;
  token_ = token;
}

UserManager::UserManager() {
}
