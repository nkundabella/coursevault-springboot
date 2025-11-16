#include "KANEZA Amandine1.h"
#include <QObject>

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    operand1 = 0.0;
    waitingForOperand = true;

    display = new QLineEdit("0", this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(display);

    QGridLayout *buttonLayout = new QGridLayout();

    for (int i = 0; i < 10; ++i) {
        QPushButton *button = new QPushButton(QString::number(i), this);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(button, &QPushButton::clicked, this, &Calculator::digitClicked);
        if (i == 0) {
            buttonLayout->addWidget(button, 3, 0);
        } else {
            buttonLayout->addWidget(button, (9 - i) / 3, (9 - i) % 3);
        }
    }

    QString operators[] = {"+", "-", "*", "/"};
    int opPositions[][2] = {{0, 3}, {1, 3}, {2, 3}, {3, 3}};
    for (int i = 0; i < 4; ++i) {
        QPushButton *button = new QPushButton(operators[i], this);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(button, &QPushButton::clicked, this, &Calculator::operatorClicked);
        buttonLayout->addWidget(button, opPositions[i][0], opPositions[i][1]);
    }

    QPushButton *equalsButton = new QPushButton("=", this);
    equalsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(equalsButton, &QPushButton::clicked, this, &Calculator::equalsClicked);
    buttonLayout->addWidget(equalsButton, 3, 2);

    QPushButton *clearButton = new QPushButton("C", this);
    clearButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearClicked);
    buttonLayout->addWidget(clearButton, 3, 1);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle("Simple Calculator");
    resize(300, 400);
}

void Calculator::digitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digit = clickedButton->text();

    if (display->text() == "0" || waitingForOperand) {
        display->setText(digit);
        waitingForOperand = false;
    } else {
        display->setText(display->text() + digit);
    }
}

void Calculator::operatorClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString newOperation = clickedButton->text();

    if (!operation.isEmpty() && !waitingForOperand) {
        equalsClicked();
    }

    operand1 = display->text().toDouble();
    operation = newOperation;
    waitingForOperand = true;
}

void Calculator::equalsClicked() {
    if (operation.isEmpty()) return;

    double operand2 = display->text().toDouble();
    double result = 0.0;

    if (operation == "+") {
        result = operand1 + operand2;
    } else if (operation == "-") {
        result = operand1 - operand2;
    } else if (operation == "*") {
        result = operand1 * operand2;
    } else if (operation == "/") {
        if (operand2 == 0.0) {
            display->setText("Error");
            return;
        }
        result = operand1 / operand2;
    }

    display->setText(QString::number(result));
    operation.clear();
    waitingForOperand = true;
}

void Calculator::clearClicked() {
    display->setText("0");
    operand1 = 0.0;
    operation.clear();
    waitingForOperand = true;
}
