#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>

class Calculator : public QWidget {
    Q_OBJECT

private:
    QLineEdit *display;
    double operand1;
    QString operation;
    bool waitingForOperand;

public:
    Calculator(QWidget *parent = nullptr);

public slots:
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();
};

#endif // CALCULATOR_H
