#include "global.h"
#include <sodium.h>

QString gate_url_prefix = "";

std::function<void(QWidget*)> repolish = [](QWidget* w) {
  w->style()->unpolish(w);
  w->style()->polish(w);
};

std::string HashPassword(const std::string& password) {
  return password;
  char hash[crypto_pwhash_STRBYTES];
  if (crypto_pwhash_str(hash, password.c_str(), password.size(),
          crypto_pwhash_OPSLIMIT_INTERACTIVE,
          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
    throw std::runtime_error("Failed to hash password");
  }
  return {hash};
}

bool CheckPassword(const std::string& password, const std::string& hash) {
  return crypto_pwhash_str_verify(hash.c_str(), password.c_str(),
             password.size()) == 0;
}
