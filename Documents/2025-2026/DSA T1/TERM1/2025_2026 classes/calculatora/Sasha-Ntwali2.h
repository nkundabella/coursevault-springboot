#ifndef SASHA-NTWALI2_H
#define SASHA-NTWALI2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digit_pressed();
    void operator_pressed();
    void on_btnClear_clicked();
    void on_btnEqual_clicked();
    void on_btnDot_clicked();

private:
    Ui::MainWindow *ui;
    QString pendingOperator;
    double leftOperand = 0;
    bool waitingForOperand = true;
};

#endif // SASHA-NTWALI2_H
