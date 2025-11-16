#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_decimal, SIGNAL(clicked()), this, SLOT(digit_pressed()));

    userIsTypingSecondNumber = false;
    resultShown = false;
    firstNum = 0;
    operation = "";
    ui->label->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();
    QString currentText = ui->label->text();

    if (resultShown || currentText == "0") {
        currentText = "";
        resultShown = false;
    }

    if (buttonText == "." && currentText.contains(".")) {
        return;
    }

    currentText += buttonText;
    ui->label->setText(currentText);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->label->setText("0");
    firstNum = 0;
    operation = "";
    userIsTypingSecondNumber = false;
    resultShown = false;
}

void MainWindow::on_pushButton_add_clicked()
{
    if (!ui->label->text().isEmpty()) {
        firstNum = ui->label->text().toDouble();
        operation = "+";
        ui->label->setText(QString::number(firstNum) + " + ");
        userIsTypingSecondNumber = true;
    }
}

void MainWindow::on_pushButton_subtract_clicked()
{
    if (!ui->label->text().isEmpty()) {
        firstNum = ui->label->text().toDouble();
        operation = "-";
        ui->label->setText(QString::number(firstNum) + " - ");
        userIsTypingSecondNumber = true;
    }
}

void MainWindow::on_pushButton_multiply_clicked()
{
    if (!ui->label->text().isEmpty()) {
        firstNum = ui->label->text().toDouble();
        operation = "*";
        ui->label->setText(QString::number(firstNum) + " * ");
        userIsTypingSecondNumber = true;
    }
}

void MainWindow::on_pushButton_divide_clicked()
{
    if (!ui->label->text().isEmpty()) {
        firstNum = ui->label->text().toDouble();
        operation = "/";
        ui->label->setText(QString::number(firstNum) + " / ");
        userIsTypingSecondNumber = true;
    }
}

void MainWindow::on_pushButton_equal_clicked()
{
    if (!userIsTypingSecondNumber || operation.isEmpty() || ui->label->text().isEmpty()) {
        return;
    }

    QString displayText = ui->label->text();
    QString secondNumStr = displayText;
    if (displayText.contains(" + ")) {
        secondNumStr = displayText.split(" + ").last();
    } else if (displayText.contains(" - ")) {
        secondNumStr = displayText.split(" - ").last();
    } else if (displayText.contains(" * ")) {
        secondNumStr = displayText.split(" * ").last();
    } else if (displayText.contains(" / ")) {
        secondNumStr = displayText.split(" / ").last();
    }
    
    double secondNum = secondNumStr.toDouble();
    double result = 0;

    if (operation == "+") {
        result = firstNum + secondNum;
    } else if (operation == "-") {
        result = firstNum - secondNum;
    } else if (operation == "*") {
        result = firstNum * secondNum;
    } else if (operation == "/") {
        if (secondNum != 0) {
            result = firstNum / secondNum;
        } else {
            ui->label->setText("Error");
            operation = "";
            userIsTypingSecondNumber = false;
            resultShown = true;
            return;
        }
    }

    ui->label->setText(QString::number(firstNum) + " " + operation + " " + QString::number(secondNum) + " = " + QString::number(result));
    firstNum = result;
    operation = "";
    userIsTypingSecondNumber = false;
    resultShown = true;
}
