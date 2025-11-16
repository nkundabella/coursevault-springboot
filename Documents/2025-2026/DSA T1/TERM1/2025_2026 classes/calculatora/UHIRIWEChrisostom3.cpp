#include "UHIRIWEChrisostom2.h"

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    display->setStyleSheet("font-size: 24px; padding: 10px;");

    QGridLayout *layout = new QGridLayout;

    
    layout->addWidget(display, 0, 0, 1, 4);

    
    QString digits[9] = {"7", "8", "9", "4", "5", "6", "1", "2", "3"};
    int row = 1, col = 0;
    for (int i = 0; i < 9; ++i) {
        QPushButton *button = createButton(digits[i], SLOT(digitClicked()));
        layout->addWidget(button, row, col);
        col++;
        if (col == 3) {
            col = 0;
            row++;
        }
    }

    QPushButton *clearButton = createButton("C", SLOT(clearClicked()));
    layout->addWidget(clearButton, 5, 0);


    QPushButton *squareButton = createButton("x²", SLOT(squareClicked()));
    layout->addWidget(squareButton, 4, 3);


    QPushButton *decimalButton = createButton(".", SLOT(decimalClicked()));
    layout->addWidget(decimalButton, 5, 1);

    QPushButton *equalButton = createButton("=", SLOT(equalClicked()));
    layout->addWidget(equalButton, 5, 2);

    QPushButton *addButton = createButton("+", SLOT(operatorClicked()));
    layout->addWidget(addButton, 5, 3);

    QPushButton *zeroButton = createButton("0", SLOT(digitClicked()));
    layout->addWidget(zeroButton, 4, 1);

    
    QPushButton *divideButton = createButton("/", SLOT(operatorClicked()));
    layout->addWidget(divideButton, 1, 3);

    QPushButton *multiplyButton = createButton("*", SLOT(operatorClicked()));
    layout->addWidget(multiplyButton, 2, 3);

    QPushButton *subtractButton = createButton("-", SLOT(operatorClicked()));
    layout->addWidget(subtractButton, 3, 3);

    setLayout(layout);
    setWindowTitle("Calculator");
    resize(400, 550);
}

QPushButton *Calculator::createButton(const QString &text, const char *member) {
    QPushButton *button = new QPushButton(text);
    button->setFixedSize(80, 80); 
    button->setStyleSheet("font-size: 18px;");
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Calculator::digitClicked() {
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (isNewInput) {
        display->setText(digit);
        isNewInput = false;
    } else {
        display->setText(display->text() + digit);
    }
}

void Calculator::decimalClicked() {
    if (isNewInput) {
        display->setText("0.");
        isNewInput = false;
    } else if (!display->text().contains(".")) {
        display->setText(display->text() + ".");
    }
}

void Calculator::operatorClicked() {
    num1 = display->text().toDouble();
    currentOperator = qobject_cast<QPushButton *>(sender())->text();
    isNewInput = true;
}

void Calculator::equalClicked() {
    num2 = display->text().toDouble();
    double result = 0.0;
    if (currentOperator == "+") {
        result = num1 + num2;
    } else if (currentOperator == "-") {
        result = num1 - num2;
    } else if (currentOperator == "*") {
        result = num1 * num2;
    } else if (currentOperator == "/") {
        if (num2 == 0) {
            display->setText("Error");
            return;
        }
        result = num1 / num2;
    }
    display->setText(QString::number(result));
    isNewInput = true;
}

void Calculator::clearClicked() {
    display->setText("0");
    isNewInput = true;
    num1 = 0.0;
    num2 = 0.0;
    currentOperator = "";
}

void Calculator::squareClicked() {
    double number = display->text().toDouble();
    double result = number * number;
    display->setText(QString::number(result));
    isNewInput = true;
}

void Calculator::keyPressEvent(QKeyEvent *event) {
    QString keyText = event->text();
    int key = event->key();

    if (keyText >= "0" && keyText <= "9") {
        if (isNewInput) {
            display->setText(keyText);
            isNewInput = false;
        } else {
            display->setText(display->text() + keyText);
        }
    } else if (keyText == ".") {
        if (isNewInput) {
            display->setText("0.");
            isNewInput = false;
        } else if (!display->text().contains(".")) {
            display->setText(display->text() + ".");
        }
    } else if (keyText == "+" || keyText == "-" || keyText == "*" || keyText == "/") {
        num1 = display->text().toDouble();
        currentOperator = keyText;
        isNewInput = true;
    } else if (key == Qt::Key_Equal || key == Qt::Key_Return || key == Qt::Key_Enter) {
        equalClicked();
    } else if (key == Qt::Key_Escape || keyText.toLower() == "c") {
        clearClicked();
    } else if (key == Qt::Key_Backspace) {
        QString text = display->text();
        if (text.length() > 1) {
            display->setText(text.left(text.length() - 1));
        } else {
            display->setText("0");
            isNewInput = true;
        }
    } else if (keyText == "s" || keyText == "^") {
        squareClicked();
    }
}