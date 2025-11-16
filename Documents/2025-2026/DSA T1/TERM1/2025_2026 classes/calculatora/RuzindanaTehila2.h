#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();
private :
    QLineEdit *display;
    QString pendingOperation;
    double firstOperand;
    bool waitingForOperand;
};

#endif // CALCULATOR_H
