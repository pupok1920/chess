#include <QApplication>

#include "handler.h"

int main(int argc, char *argv[])
{
    struct QGuiApplicationMy : public QApplication {
        QGuiApplicationMy(int argc, char **argv) : QApplication(argc, argv) {}
    } app(argc, argv);

    Handler handler;

    return app.exec();
}
