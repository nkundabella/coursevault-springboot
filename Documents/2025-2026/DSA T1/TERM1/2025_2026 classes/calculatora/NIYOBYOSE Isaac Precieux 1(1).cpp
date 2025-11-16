#include "calculator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <cmath>
#include <QSizePolicy>
#include <QMessageBox>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), waitingForOperand(true), pendingValue(0.0)
{
    setWindowTitle("Isaac's Calculator");
    setFixedSize(350, 500);
    setStyleSheet("QMainWindow { background-color: #000000; }");
    
    createUI();
    
    display->setText("0");
    display->installEventFilter(this); // Install event filter
}

Calculator::~Calculator()
{
}

void Calculator::createUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setFocusPolicy(Qt::StrongFocus);
    setFocusProxy(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    display->setStyleSheet(
        "QLineEdit { background-color: #1c1c1e; border: none; color: white; "
        "font-size: 40px; font-weight: bold; padding: 20px; }"
    );
    mainLayout->addWidget(display);
    
    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->setSpacing(8);
    
    buttonLayout->addWidget(createButton("AC", functionButtonStyle), 0, 0);
    buttonLayout->addWidget(createButton("C", functionButtonStyle), 0, 1);
    buttonLayout->addWidget(createButton("⌫", functionButtonStyle), 0, 2);
    buttonLayout->addWidget(createButton("÷", operatorButtonStyle), 0, 3);
    
    buttonLayout->addWidget(createButton("7", numberButtonStyle), 1, 0);
    buttonLayout->addWidget(createButton("8", numberButtonStyle), 1, 1);
    buttonLayout->addWidget(createButton("9", numberButtonStyle), 1, 2);
    buttonLayout->addWidget(createButton("×", operatorButtonStyle), 1, 3);
    
    buttonLayout->addWidget(createButton("4", numberButtonStyle), 2, 0);
    buttonLayout->addWidget(createButton("5", numberButtonStyle), 2, 1);
    buttonLayout->addWidget(createButton("6", numberButtonStyle), 2, 2);
    buttonLayout->addWidget(createButton("-", operatorButtonStyle), 2, 3);
    
    buttonLayout->addWidget(createButton("1", numberButtonStyle), 3, 0);
    buttonLayout->addWidget(createButton("2", numberButtonStyle), 3, 1);
    buttonLayout->addWidget(createButton("3", numberButtonStyle), 3, 2);
    buttonLayout->addWidget(createButton("+", operatorButtonStyle), 3, 3);
    
    buttonLayout->addWidget(createButton("0", numberButtonStyle), 4, 0);
    buttonLayout->addWidget(createButton(".", numberButtonStyle), 4, 1);
    buttonLayout->addWidget(createButton("=", operatorButtonStyle), 4, 2, 1, 2);
    
    mainLayout->addLayout(buttonLayout);
}

QPushButton *Calculator::createButton(const QString &text, const QString &style)
{
    QPushButton *button = new QPushButton(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setStyleSheet(style);
    
    buttonMap[text] = button;
    
    if (text >= "0" && text <= "9" || text == ".") {
        connect(button, &QPushButton::clicked, this, &Calculator::digitClicked);
    } else if (text == "+" || text == "-" || text == "×" || text == "÷") {
        connect(button, &QPushButton::clicked, this, &Calculator::operatorClicked);
    } else if (text == "=") {
        connect(button, &QPushButton::clicked, this, &Calculator::equalClicked);
    } else if (text == "AC") {
        connect(button, &QPushButton::clicked, this, &Calculator::clearAll);
    } else if (text == "C") {
        connect(button, &QPushButton::clicked, this, &Calculator::clearEntry);
    } else if (text == "⌫") {
        connect(button, &QPushButton::clicked, this, &Calculator::backspaceClicked);
    }
    
    return button;
}

bool Calculator::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == display && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        keyPressEvent(keyEvent);
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void Calculator::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed:" << event->key() << "Text:" << event->text() << "Modifiers:" << event->modifiers();
    QString keyText = event->text();

    switch (event->key()) {
    case Qt::Key_0: case Qt::Key_1: case Qt::Key_2: case Qt::Key_3:
    case Qt::Key_4: case Qt::Key_5: case Qt::Key_6:
    case Qt::Key_7: case Qt::Key_8: case Qt::Key_9:
        // Handle both regular and numpad digits (Qt::Key_0 to Key_9 are used for both)
        if (buttonMap.contains(keyText)) {
            buttonMap[keyText]->click();
        }
        break;
    case Qt::Key_Plus:
        // Handle both regular and numpad "+"
        if (buttonMap.contains("+")) {
            buttonMap["+"]->click();
        }
        break;
    case Qt::Key_Minus:
        // Handle both regular and numpad "-"
        if (buttonMap.contains("-")) {
            buttonMap["-"]->click();
        }
        break;
    case Qt::Key_Asterisk:
        // Handle both regular and numpad "*"
        if (buttonMap.contains("×")) {
            buttonMap["×"]->click();
        }
        break;
    case Qt::Key_Slash:
        // Handle both regular and numpad "/"
        if (buttonMap.contains("÷")) {
            buttonMap["÷"]->click();
        }
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        // Handle Enter/Return for both regular and numpad
        if (buttonMap.contains("=")) {
            buttonMap["="]->click();
        }
        break;
    case Qt::Key_Escape:
        clearAll();
        break;
    case Qt::Key_Backspace:
        backspaceClicked();
        break;
    case Qt::Key_Period:
    case Qt::Key_Comma: // Sometimes numpad decimal is Key_Comma
        // Handle both regular and numpad "."
        if (buttonMap.contains(".")) {
            buttonMap["."]->click();
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digitValue = clickedButton->text();
    
    if (display->text() == "0" && digitValue != ".") {
        display->clear();
    }
    
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    
    display->setText(display->text() + digitValue);
}

void Calculator::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        double result = calculate(pendingValue, operand, pendingOperator);
        display->setText(QString::number(result));
        operand = result;
    } else {
        pendingValue = operand;
    }
    
    pendingOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();
    
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        double result = calculate(pendingValue, operand, pendingOperator);
        display->setText(QString::number(result));
        pendingValue = result;
        pendingOperator.clear();
        waitingForOperand = true;
    }
}

void Calculator::clearAll()
{
    display->setText("0");
    pendingValue = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}

void Calculator::clearEntry()
{
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::backspaceClicked()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

double Calculator::calculate(double left, double right, const QString &op)
{
    if (op == "+") {
        return left + right;
    } else if (op == "-") {
        return left - right;
    } else if (op == "×") {
        return left * right;
    } else if (op == "÷") {
        if (right == 0.0) {
             QMessageBox::critical(nullptr, "Math Error", "Division by zero is not allowed!");
            return 0.0;
        }
        return left / right;
    }
    return right;
}

void Calculator::abortOperation()
{
    display->setText("Error");
    pendingValue = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}