#include "BattleCity.h"
#include <QApplication>
#include <QQmlContext>
#include <QKeyEvent>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

int main(int argc, char **argv) {
  struct QGuiApplicationMy : public QApplication {
    QGuiApplicationMy(int argc, char **argv) : QApplication(argc, argv) {}

    bool notify(QObject *receiver, QEvent *event) override {
      if (QEvent::KeyPress == event->type() || QEvent::KeyRelease == event->type()) {
        if (QKeyEvent *key_event = dynamic_cast<QKeyEvent *>(event)) {
          if (Qt::Key_Escape == key_event->key()) {
            exit(0);
          }
          else
            game.event(*key_event);
        }
      }
      return QApplication::notify(receiver, event);
    }

    BattleCity game;

  } app(argc, argv);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("game", &app.game);
  engine.load(QUrl(QStringLiteral("qml/main.qml")));

  return app.exec();
}
