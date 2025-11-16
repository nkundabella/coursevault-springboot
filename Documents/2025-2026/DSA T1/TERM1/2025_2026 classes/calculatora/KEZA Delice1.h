// mainwindow.h
#ifndef KEZA DELICE1_H
#define KEZA DELICE1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDigitPressed();
    void onOperatorPressed();
    void onEqualsPressed();
    void onClearPressed();

private:
    Ui::MainWindow *ui;
    double firstNumber = 0.0;
    QString pendingOperator;
    bool waitingForOperand = true;

    void appendDigit(const QString &digit);
    double calculate(double left, double right, const QString &op);
};

#endif // KEZA DELICE1_H
