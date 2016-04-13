#include <QApplication>
#include <QQmlContext>
#include <QKeyEvent>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QJSValue>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
