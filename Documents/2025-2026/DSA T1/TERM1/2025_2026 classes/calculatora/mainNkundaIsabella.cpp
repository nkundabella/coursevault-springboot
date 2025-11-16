#include <QApplication>
#include "NkundaIsabella.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calc;
    calc.setWindowTitle("Simple Calculator");
    calc.resize(300, 400);
    calc.show();

    return app.exec();
}