#include <itemmodel.h>
#include <QApplication>
#include <QQmlContext>
#include <QKeyEvent>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QJSValue>

int main(int argc, char *argv[])
{   
    struct QGuiApplicationMy : public QApplication {
        QGuiApplicationMy(int argc, char **argv) : QApplication(argc, argv) {}

        void implemModel();
        ItemModel model;
    } app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataModel", &app.model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
