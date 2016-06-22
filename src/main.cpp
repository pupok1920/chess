#include "boardmodel.h"
#include <QApplication>
#include <QQmlContext>
#include <QKeyEvent>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

int main(int argc, char *argv[])
{   
    struct QGuiApplicationMy : public QApplication {
        QGuiApplicationMy(int argc, char **argv) : QApplication(argc, argv) {}
    } app(argc, argv);

    BoardModel board;
    board.initialise();

    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("boardModel", &board);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
