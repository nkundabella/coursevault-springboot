#include "NIYONKURU_Gloria.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);   // Create the application
    MainWindow w;                 // Create your main window
    w.show();                     // Show the main window
    return a.exec();              // Run the application loop
}

