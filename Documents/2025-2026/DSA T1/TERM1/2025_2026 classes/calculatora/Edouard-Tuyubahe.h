#pragma once

#include <QtWidgets/QWidget>

class QPushButton;
class QLineEdit;

class CalcWindow : public QWidget {
    Q_OBJECT
public:
    explicit CalcWindow(QWidget* parent = nullptr);

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onDotClicked();

private:
    void appendDigit(const QString& digitText);
    void applyOperator(const QChar opChar);
    void compute();
    void updateDisplay(const QString& text);

    QLineEdit* display;
    QString currentNumber;
    QString previousNumber;
    QChar currentOperator;
    bool newNumber;
};


