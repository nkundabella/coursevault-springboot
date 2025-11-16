



#include "KEZA Delice1.h"
#include "ui_KEZA Delice1.h"
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize calculator state
    waitingForOperand = true;
    firstNumber = 0.0;
    pendingOperator.clear();

    // Connect digit buttons 0-9
    connect(ui->button_0, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_1, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_2, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_3, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_4, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_5, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_6, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_7, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_8, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->button_9, &QPushButton::clicked, this, &MainWindow::onDigitPressed);
    connect(ui->buttonDecimal, &QPushButton::clicked, this, &MainWindow::onDigitPressed);

    // Connect operator buttons
    connect(ui->buttonPlus, &QPushButton::clicked, this, &MainWindow::onOperatorPressed);
    connect(ui->buttonMinus, &QPushButton::clicked, this, &MainWindow::onOperatorPressed);
    connect(ui->buttonTimes, &QPushButton::clicked, this, &MainWindow::onOperatorPressed);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &MainWindow::onOperatorPressed);

    // Connect equals and clear
    connect(ui->buttonEqual, &QPushButton::clicked, this, &MainWindow::onEqualsPressed);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::onClearPressed);

    // Set initial display
    ui->display->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Digit button pressed
void MainWindow::onDigitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString digit = button->text();
    appendDigit(digit);
}

// Append digit to display
void MainWindow::appendDigit(const QString &digit)
{
    QString currentText = ui->display->text();
    if (currentText == "Error") currentText = "0";

    if (waitingForOperand) {
        ui->display->setText(digit);
        waitingForOperand = false;
    } else {
        if (currentText == "0" && digit != ".") {
            ui->display->setText(digit);
        } else {
            if (digit == "." && currentText.contains(".")) return;
            ui->display->setText(currentText + digit);
        }
    }
}

// Operator button pressed
void MainWindow::onOperatorPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();
    QString currentText = ui->display->text();

    if (currentText == "Error") {
        ui->display->setText("0");
        return;
    }

    double currentValue = currentText.toDouble();

    // If an operator is already pending, calculate first
    if (!pendingOperator.isEmpty()) {
        double result = calculate(firstNumber, currentValue, pendingOperator);
        ui->display->setText(QString::number(result));
        currentValue = result;
    }

    firstNumber = currentValue;
    pendingOperator = op;
    waitingForOperand = true;
}

// Equals button pressed
void MainWindow::onEqualsPressed()
{
    if (pendingOperator.isEmpty()) return;

    QString currentText = ui->display->text();
    if (currentText == "Error") {
        ui->display->setText("0");
        return;
    }

    double secondNumber = currentText.toDouble();
    double result = calculate(firstNumber, secondNumber, pendingOperator);

    ui->display->setText(QString::number(result));
    pendingOperator.clear();
    waitingForOperand = true;
}

// Clear button pressed
void MainWindow::onClearPressed()
{
    ui->display->setText("0");
    firstNumber = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}

// Perform calculation
double MainWindow::calculate(double left, double right, const QString &op)
{
    qDebug() << "Calculating:" << left << op << right;

    if (op == "+" ) return left + right;
    if (op == "-" ) return left - right;
    if (op == "*" || op == "×" || op == "x") return left * right;
    if (op == "/" || op == "÷") {
        if (right == 0) {
            ui->display->setText("Error");
            return 0;
        }
        return left / right;
    }

    qDebug() << "Unknown operator:" << op;
    return 0;
}

