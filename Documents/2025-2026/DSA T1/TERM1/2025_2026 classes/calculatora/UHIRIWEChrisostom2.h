#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QKeyEvent>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void digitClicked();
    void decimalClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();
    void squareClicked();

private:
    QLineEdit *display;
    double num1 = 0.0;
    double num2 = 0.0;
    QString currentOperator;
    bool isNewInput = true;

    QPushButton *createButton(const QString &text, const char *member);
};

#endif  