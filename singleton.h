#pragma once
#include "global.h"

template <typename T>
class Singleton {
public:
  static std::shared_ptr<T> GetInstance() {
    static std::shared_ptr<T> instance(new T);
    return instance;
  }

  void PrintAddress() { fmt::print("{}'s address={}\n", typeid(*this).name(), static_cast<void*>(this)); }
  ~Singleton() { fmt::print("{} destructed\n", typeid(*this).name()); }

  Singleton(const Singleton<T>&) = delete;
  Singleton(Singleton<T>&&) = delete;
  Singleton& operator=(const Singleton<T>&) = delete;
  Singleton& operator=(Singleton<T>&&) = delete;

protected:
  Singleton() = default;
};

class MySingle : public Singleton<MySingle> {
  friend class Singleton<MySingle>;

public:
  ~MySingle() {
  }

private:
  MySingle() {
  }
};