#include "Sasha-Ntwali2.h"
#include "ui_Sasha-Ntwali1.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect digit buttons
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::digit_pressed);

    // Connect operator buttons
    connect(ui->btnPlus, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->btnMinus, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->btnMul, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->btnMod, &QPushButton::clicked, this, &MainWindow::operator_pressed);

    // Decimal
    connect(ui->btnDot, &QPushButton::clicked, this, &MainWindow::on_btnDot_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    if (waitingForOperand) {
        ui->display->clear();
        waitingForOperand = false;
    }
    ui->display->setText(ui->display->text() + button->text());
}

void MainWindow::operator_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    double operand = ui->display->text().toDouble();

    if (!pendingOperator.isEmpty()) {
        if (pendingOperator == "+") leftOperand += operand;
        else if (pendingOperator == "-") leftOperand -= operand;
        else if (pendingOperator == "*") leftOperand *= operand;
        else if (pendingOperator == "/") {
            if (operand != 0)
                leftOperand /= operand;
            else {
                ui->display->setText("Error");
                return;
            }
        }
        else if (pendingOperator == "%") {
            int left = static_cast<int>(leftOperand);
            int right = static_cast<int>(operand);
            if (right != 0)
                leftOperand = left % right;
            else {
                ui->display->setText("Error");
                return;
            }
        }
    } else {
        leftOperand = operand;
    }

    pendingOperator = button->text();
    waitingForOperand = true;
}

void MainWindow::on_btnClear_clicked()
{
    leftOperand = 0;
    pendingOperator.clear();
    ui->display->clear();
    waitingForOperand = true;
}

void MainWindow::on_btnEqual_clicked()
{
    double operand = ui->display->text().toDouble();

    if (pendingOperator == "+") leftOperand += operand;
    else if (pendingOperator == "-") leftOperand -= operand;
    else if (pendingOperator == "*") leftOperand *= operand;
    else if (pendingOperator == "/") {
        if (operand != 0)
            leftOperand /= operand;
        else {
            ui->display->setText("Error");
            return;
        }
    }
    else if (pendingOperator == "%") {
        int left = static_cast<int>(leftOperand);
        int right = static_cast<int>(operand);
        if (right != 0)
            leftOperand = left % right;
        else {
            ui->display->setText("Error");
            return;
        }
    }

    ui->display->setText(QString::number(leftOperand));
    pendingOperator.clear();
    waitingForOperand = true;
}

void MainWindow::on_btnDot_clicked()
{
    if (waitingForOperand) {
        ui->display->setText("0");
        waitingForOperand = false;
    }

    if (!ui->display->text().contains(".")) {
        ui->display->setText(ui->display->text() + ".");
    }
}
