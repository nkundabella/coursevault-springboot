#include "NkundaIsabella.h"
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QFont>
#include <QRegularExpression>

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    display = new QLineEdit("0");
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);
    display->setStyleSheet("background-color: #222222; color: white; padding: 10px; border-radius: 10px; font-size: 16px;");
    display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->addWidget(display, 0, 0, 1, 4);

    QStringList buttons = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "+/-", "0", ".", "+"
    };

    pendingOperand = 0;
    waitingForOperand = true;
    int pos = 0;

    for (int row = 1; row <= 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            QString text = buttons[pos];
            QPushButton *btn = new QPushButton(text);
            btn->setFont(QFont("Arial", 12));
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layout->addWidget(btn, row, col);
            connect(btn, &QPushButton::clicked, this, &Calculator::onButtonClicked);
            if (text == "+" || text == "-" || text == "*" || text == "/") {
                btn->setStyleSheet("background-color: #FF69B4; color: white; border-radius: 10px;");
            } else {
                btn->setStyleSheet("background-color: #333333; color: white; border-radius: 10px;");
            }
            pos++;
        }
    }

    QPushButton *c = new QPushButton("C");
    c->setFont(QFont("Arial", 12));
    c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    c->setStyleSheet("background-color: #333333; color: white; border-radius: 10px;");
    connect(c, &QPushButton::clicked, this, &Calculator::onButtonClicked);
    layout->addWidget(c, 5, 0);

    QPushButton *ce = new QPushButton("CE");
    ce->setFont(QFont("Arial", 12));
    ce->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ce->setStyleSheet("background-color: #333333; color: white; border-radius: 10px;");
    connect(ce, &QPushButton::clicked, this, &Calculator::onButtonClicked);
    layout->addWidget(ce, 5, 1);

    QPushButton *equals = new QPushButton("=");
    equals->setFont(QFont("Arial", 12));
    equals->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    equals->setStyleSheet("background-color: #32CD32; color: white; border-radius: 10px;");
    connect(equals, &QPushButton::clicked, this, &Calculator::onButtonClicked);
    layout->addWidget(equals, 5, 2, 1, 2);

    this->setLayout(layout);
    this->setStyleSheet("background-color: black;");
}

void Calculator::onButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;
    QString text = clickedButton->text();
    handleInput(text);
}

void Calculator::handleInput(const QString &text) {
    if (text == "CE") {
        display->setText("0");
        pendingOperator.clear();
        pendingOperand = 0;
        waitingForOperand = true;
    } else if (text == "C") {
        QString current = display->text();
        if (current.length() > 1) {
            display->setText(current.left(current.length() - 1));
        } else {
            display->setText("0");
        }
        waitingForOperand = false;
    } else if (text == "+/-") {
        QString current = display->text();
        if (current.startsWith("-"))
            display->setText(current.mid(1));
        else if (current != "0")
            display->setText("-" + current);
    } else if (text == "=") {
        double operand = display->text().toDouble();
        if (!pendingOperator.isEmpty()) {
            calculate(operand, pendingOperator);
            pendingOperator.clear();
        }
        waitingForOperand = true;
    } else if (text == "+" || text == "-" || text == "*" || text == "/") {
        double operand = display->text().toDouble();
        if (!pendingOperator.isEmpty()) {
            calculate(operand, pendingOperator);
        } else {
            pendingOperand = operand;
        }
        pendingOperator = text;
        waitingForOperand = true;
    } else {
        if (display->text() == "0" || waitingForOperand) {
            display->clear();
            waitingForOperand = false;
        }
        display->setText(display->text() + text);
    }
}

void Calculator::keyPressEvent(QKeyEvent *event) {
    if (!event->text().isEmpty()) {
        QString text = event->text();
        if (text[0].isDigit() || text == "." || text == "+" || text == "-" || text == "*" || text == "/" || text == "=") {
            handleInput(text);
        }
    } else {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            handleInput("=");
        }
    }
    QWidget::keyPressEvent(event); 
}

void Calculator::abortOperation() {
    display->setText("Math Error");
    pendingOperand = 0;
    pendingOperator.clear();
    waitingForOperand = true;
}

bool Calculator::calculate(double rightOperand, const QString &operatorText) {
    if (operatorText == "+")
        pendingOperand += rightOperand;
    else if (operatorText == "-")
        pendingOperand -= rightOperand;
    else if (operatorText == "*")
        pendingOperand *= rightOperand;
    else if (operatorText == "/") {
        if (rightOperand == 0.0) {
            abortOperation();
            return false;
        }
        pendingOperand /= rightOperand;
    }
    display->setText(QString::number(pendingOperand));
    return true;
}