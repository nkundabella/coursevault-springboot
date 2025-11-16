#include "calculator.h"
#include <QRegularExpression>
#include <QDebug>

Calculator::Calculator(QWidget *parent) : QMainWindow(parent), waitingForOperand(true) {
    setupUI();
    setWindowTitle("Qt Calculator");
    resize(300, 400);
}

Calculator::~Calculator() {

}

void Calculator::setupUI() {
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaximumHeight(50);
    display->setStyleSheet("QLineEdit { font-size: 18px; padding: 10px; }");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);

    createButtons();
    mainLayout->addLayout(createButtons());

    centralWidget->setLayout(mainLayout);
}

QVBoxLayout* Calculator::createButtons() {
    QVBoxLayout *buttonLayout = new QVBoxLayout;

    
    QGridLayout *digitLayout = new QGridLayout;

    QStringList digits = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", ".", "="};

    int pos = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (pos < digits.size()) {
                QString text = digits[pos];
                QPushButton *button;

                if (text == "=") {
                    button = createButton(text, SLOT(equalsClicked()));
                    button->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-size: 16px; }");
                } else if (text == ".") {
                    button = createButton(text, SLOT(decimalClicked()));
                } else {
                    button = createButton(text, SLOT(digitClicked()));
                }

                digitLayout->addWidget(button, row, col);
                pos++;
            }
        }
    }

    buttonLayout->addLayout(digitLayout);

    
    QHBoxLayout *operatorLayout = new QHBoxLayout;

    QStringList operators = {"+", "-", "*", "/", "C"};
    for (const QString& op : operators) {
        QPushButton *button = createButton(op, SLOT(operatorClicked()));
        if (op == "C") {
            button->setStyleSheet("QPushButton { background-color: #f44336; color: white; font-size: 16px; }");
        } else {
            button->setStyleSheet("QPushButton { background-color: #2196F3; color: white; font-size: 16px; }");
        }
        operatorLayout->addWidget(button);
    }

    buttonLayout->addLayout(operatorLayout);

    return buttonLayout;
}

QPushButton* Calculator::createButton(const QString& text, const char* slot) {
    QPushButton *button = new QPushButton(text);
    button->setMinimumSize(60, 40);
    connect(button, SIGNAL(clicked()), this, slot);
    return button;
}

void Calculator::digitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString digit = clickedButton->text();

    if (waitingForOperand) {
        display->setText(digit);
        waitingForOperand = false;
    } else {
        QString currentText = display->text();
        display->setText(currentText + digit);
    }
}

void Calculator::operatorClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString clickedOperator = clickedButton->text();

    if (clickedOperator == "C") {
        clearClicked();
        return;
    }

    if (!currentOperator.isEmpty()) {
        calculateResult();
    }

    previousInput = display->text();
    currentOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalsClicked() {
    calculateResult();
    currentOperator.clear();
    waitingForOperand = true;
}

void Calculator::clearClicked() {
    display->setText("0");
    currentInput.clear();
    previousInput.clear();
    currentOperator.clear();
    waitingForOperand = true;
}

void Calculator::decimalClicked() {
    if (waitingForOperand) {
        display->setText("0.");
        waitingForOperand = false;
    } else if (display->text().indexOf('.') == -1) {
        display->setText(display->text() + ".");
    }
}

void Calculator::calculateResult() {
    if (currentOperator.isEmpty() || previousInput.isEmpty()) {
        return;
    }

    double operand1 = previousInput.toDouble();
    double operand2 = display->text().toDouble();
    double result = 0.0;

    if (currentOperator == "+") {
        result = operand1 + operand2;
    } else if (currentOperator == "-") {
        result = operand1 - operand2;
    } else if (currentOperator == "*") {
        result = operand1 * operand2;
    } else if (currentOperator == "/") {
        if (operand2 != 0.0) {
            result = operand1 / operand2;
        } else {
            display->setText("Error: Division by zero");
            return;
        }
    }

    display->setText(QString::number(result, 'g', 10));
}
