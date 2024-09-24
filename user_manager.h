//
// Created by summer on 2024/9/20.
//

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <QObject>
#include "singleton.h"


class UserManager : public QObject, public Singleton<UserManager> {
  friend class Singleton<UserManager>;
  Q_OBJECT

public:
  ~UserManager();
  void SetUid(int uid);
  void SetName(const QString& name);
  void SetToken(const QString& token);
  void SetUser(int uid, const QString& name, const QString& token);

private:
  UserManager();

  QString name_;
  QString token_;
  int uid_;
};


#endif //USER_MANAGER_H
