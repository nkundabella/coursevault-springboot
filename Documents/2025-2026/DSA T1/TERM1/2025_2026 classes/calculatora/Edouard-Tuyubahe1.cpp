#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    CalcWindow w;
    w.show();
    return app.exec();
}


