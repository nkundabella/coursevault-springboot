#include "calculator.h"
#include <QApplication>
#include <QFont>
#include <QMessageBox>
#include <cmath>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), sumInMemory(0.0), sumSoFar(0.0), waitingForOperand(true)
{
    setWindowTitle("Calculator");
    setFixedSize(300, 400);
    // Apply a simple dark theme for better contrast/visibility
    setStyleSheet(
        "QWidget { background-color: #1e1e1e; }"
        "QLineEdit { background-color: #2d2d2d; color: #ffffff; border: 2px solid #444; padding: 10px; }"
        "QPushButton { background-color: #3a3a3a; color: #ffffff; border: 1px solid #555; border-radius: 6px; }"
        "QPushButton:pressed { background-color: #2f2f2f; }"
    );
    
    // Create display
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    // The display styling is now handled by the widget-wide stylesheet above
    
    createButtons();
    setupLayout();
}

void Calculator::createButtons()
{
    // Create digit buttons (0-9)
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = new QPushButton(QString::number(i));
        digitButtons[i]->setMinimumSize(60, 60);
        digitButtons[i]->setFont(QFont("Arial", 14));
        connect(digitButtons[i], &QPushButton::clicked, this, &Calculator::digitClicked);
    }
    
    // Create operation buttons
    addButton = new QPushButton("+");
    subtractButton = new QPushButton("-");
    multiplyButton = new QPushButton("×");
    divideButton = new QPushButton("÷");
    equalButton = new QPushButton("=");
    clearButton = new QPushButton("Clear");
    decimalButton = new QPushButton(".");
    
    // Set button sizes and fonts
    QList<QPushButton*> operatorButtons = {addButton, subtractButton, multiplyButton, 
                                          divideButton, equalButton, clearButton, decimalButton};
    
    for (QPushButton* button : operatorButtons) {
        button->setMinimumSize(60, 60);
        button->setFont(QFont("Arial", 14));
    }
    
    // Set special styling for operation buttons
    QString operatorStyle =
        "QPushButton { background-color: #5a5a5a; color: #ffffff; border: 1px solid #777; } "
        "QPushButton:pressed { background-color: #4e4e4e; }";
    
    addButton->setStyleSheet(operatorStyle);
    subtractButton->setStyleSheet(operatorStyle);
    multiplyButton->setStyleSheet(operatorStyle);
    divideButton->setStyleSheet(operatorStyle);
    
    equalButton->setStyleSheet(
        "QPushButton { background-color: #2e7d32; color: #ffffff; border: 1px solid #1b5e20; } "
        "QPushButton:pressed { background-color: #256628; }"
    );
    
    clearButton->setStyleSheet(
        "QPushButton { background-color: #c62828; color: #ffffff; border: 1px solid #8e0000; } "
        "QPushButton:pressed { background-color: #a01f1f; }"
    );
    
    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &Calculator::operatorClicked);
    connect(subtractButton, &QPushButton::clicked, this, &Calculator::operatorClicked);
    connect(multiplyButton, &QPushButton::clicked, this, &Calculator::operatorClicked);
    connect(divideButton, &QPushButton::clicked, this, &Calculator::operatorClicked);
    connect(equalButton, &QPushButton::clicked, this, &Calculator::equalClicked);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearClicked);
    connect(decimalButton, &QPushButton::clicked, this, &Calculator::digitClicked);
}

void Calculator::setupLayout()
{
    mainLayout = new QGridLayout;
    
    // Add display at the top
    mainLayout->addWidget(display, 0, 0, 1, 4);
    
    // Add clear button
    mainLayout->addWidget(clearButton, 1, 0, 1, 4);
    
    // Add number buttons in calculator layout
    mainLayout->addWidget(digitButtons[7], 2, 0);
    mainLayout->addWidget(digitButtons[8], 2, 1);
    mainLayout->addWidget(digitButtons[9], 2, 2);
    mainLayout->addWidget(divideButton, 2, 3);
    
    mainLayout->addWidget(digitButtons[4], 3, 0);
    mainLayout->addWidget(digitButtons[5], 3, 1);
    mainLayout->addWidget(digitButtons[6], 3, 2);
    mainLayout->addWidget(multiplyButton, 3, 3);
    
    mainLayout->addWidget(digitButtons[1], 4, 0);
    mainLayout->addWidget(digitButtons[2], 4, 1);
    mainLayout->addWidget(digitButtons[3], 4, 2);
    mainLayout->addWidget(subtractButton, 4, 3);
    
    mainLayout->addWidget(digitButtons[0], 5, 0);
    mainLayout->addWidget(decimalButton, 5, 1);
    mainLayout->addWidget(equalButton, 5, 2);
    mainLayout->addWidget(addButton, 5, 3);
    
    setLayout(mainLayout);
}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digitValue = clickedButton->text();
    
    // When starting a new operand
    if (waitingForOperand) {
        if (digitValue == ".") {
            display->setText("0.");
        } else {
            // Replace the current display with the first digit
            display->setText(digitValue);
        }
        waitingForOperand = false;
        return;
    }
    
    // Prevent multiple decimals in the same number
    if (digitValue == "." && display->text().contains(".")) {
        return;
    }
    
    // Replace leading 0 unless entering a decimal
    if (display->text() == "0" && digitValue != ".") {
        display->setText(digitValue);
        return;
    }
    
    display->setText(display->text() + digitValue);
}

void Calculator::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();
    
    double operand = display->text().toDouble();
    
    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(sumSoFar, pendingMultiplicativeOperator, operand)) {
            clearClicked();
            return;
        }
        display->setText(QString::number(sumSoFar));
        operand = sumSoFar;
        sumSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(sumInMemory, pendingAdditiveOperator, operand)) {
            clearClicked();
            return;
        }
        display->setText(QString::number(sumInMemory));
    } else {
        sumInMemory = operand;
    }
    
    if (clickedOperator == "×" || clickedOperator == "÷") {
        sumSoFar = operand;
        pendingMultiplicativeOperator = clickedOperator;
    } else {
        pendingAdditiveOperator = clickedOperator;
    }
    
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    
    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(sumSoFar, pendingMultiplicativeOperator, operand)) {
            clearClicked();
            return;
        }
        operand = sumSoFar;
        sumSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(sumInMemory, pendingAdditiveOperator, operand)) {
            clearClicked();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumInMemory = operand;
    }
    
    display->setText(QString::number(sumInMemory));
    sumInMemory = 0.0;
    waitingForOperand = true;
}

void Calculator::clearClicked()
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

double Calculator::calculate(double leftOperand, const QString &pendingOperator, double rightOperand)
{
    if (pendingOperator == "+") {
        sumInMemory = leftOperand + rightOperand;
    } else if (pendingOperator == "-") {
        sumInMemory = leftOperand - rightOperand;
    } else if (pendingOperator == "×") {
        sumSoFar = leftOperand * rightOperand;
    } else if (pendingOperator == "÷") {
        if (rightOperand == 0.0) {
            QMessageBox::warning(this, "Calculator", "Division by zero error!");
            return false;
        }
        sumSoFar = leftOperand / rightOperand;
    }
    return true;
}
