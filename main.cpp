#include <QApplication>


#include "global.h"
#include "mainwindow.h"
#include "qapplication.h"
#include "qnamespace.h"
#include "singleton.h"
#include "sodium.h"

int main(int argc, char* argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication a(argc, argv);

  QFile qss(":/style/stylesheet.qss");
  if (qss.open(QFile::ReadOnly)) {
    QString style = qss.readAll();
    a.setStyleSheet(style);
    qss.close();
  } else {
    fmt::print("open qss failed!\n");
  }

  if (sodium_init() < 0) {
    fmt::print("sodium init failed!\n");
    return -1;
  }

  QString file_name = "config.ini";
  QString file_path = QApplication::applicationDirPath() + QDir::separator() +
                      file_name;
  QSettings settings(file_path, QSettings::IniFormat);
  auto gate_host = settings.value("gate-server/host").toString();
  auto gate_port = settings.value("gate-server/port").toString();
  gate_url_prefix = "http://" + gate_host + ":" + gate_port;

  MainWindow w;
  w.show();
  return a.exec();
}
