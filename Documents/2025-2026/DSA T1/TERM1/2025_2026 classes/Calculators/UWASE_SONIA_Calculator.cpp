#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QRegularExpression>
#include <cmath>
#include<QJSEngine>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->btnOpenBracket, &QPushButton::clicked, this, &MainWindow::on_bracket_pressed);
    connect(ui->btnCloseBracket, &QPushButton::clicked, this, &MainWindow::on_bracket_pressed);


    connect(ui->btnSquare, &QPushButton::clicked, this, &MainWindow::on_square_pressed);
    connect(ui->btnSqrt, &QPushButton::clicked, this, &MainWindow::on_sqrt_pressed);
    connect(ui->btnInverse, &QPushButton::clicked, this, &MainWindow::on_inverse_pressed);
    connect(ui->btnPercent, &QPushButton::clicked, this, &MainWindow::on_percent_pressed);


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
    connect(ui->btnDot, &QPushButton::clicked, this, &MainWindow::dot_pressed);


    connect(ui->btnPlus, &QPushButton::clicked, this, &MainWindow::binary_operation_pressed);
    connect(ui->btnMinus, &QPushButton::clicked, this, &MainWindow::binary_operation_pressed);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &MainWindow::binary_operation_pressed);
    connect(ui->btnDivide, &QPushButton::clicked, this, &MainWindow::binary_operation_pressed);


    connect(ui->btnEqual, &QPushButton::clicked, this, &MainWindow::on_equal_pressed);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::on_clear_pressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString currentText = ui->display->text();
    ui->display->setText(currentText + button->text());
}

void MainWindow::binary_operation_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    if (operation.isEmpty()) {
        firstNum = ui->display->text().toDouble();
        operation = button->text();
        ui->display->setText(ui->display->text() + " " + operation + " ");
    }
}

void MainWindow::dot_pressed()
{
    QString currentText = ui->display->text();

    QStringList parts = currentText.split(QRegularExpression("[+\\-×÷]"));
    QString lastPart = parts.last();

    if (!lastPart.contains("."))
        ui->display->setText(currentText + ".");
}

void MainWindow::on_equal_pressed()
{

    QString expr = ui->display->text();


    expr.replace("×", "*");
    expr.replace("÷", "/");

    QJSEngine engine;
    QJSValue result = engine.evaluate(expr);

    if (result.isError()) {
        ui->display->setText("Error");
    } else {
        ui->display->setText(result.toString());
        firstNum = result.toNumber();
    }
}

void MainWindow::on_clear_pressed()
{
    ui->display->clear();
    operation = "";
    firstNum = 0;
}

void MainWindow::on_bracket_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString currentText = ui->display->text();
    ui->display->setText(currentText + button->text());
}


void MainWindow::on_square_pressed()
{
    bool ok;
    double value = ui->display->text().toDouble(&ok);
    if (ok) {
        double result = value * value;
        ui->display->setText(QString::number(result));
    }
}


void MainWindow::on_sqrt_pressed()
{
    bool ok;
    double value = ui->display->text().toDouble(&ok);
    if (ok && value >= 0) {
        double result = sqrt(value);
        ui->display->setText(QString::number(result));
    } else {
        ui->display->setText("Error");
    }
}


void MainWindow::on_inverse_pressed()
{
    bool ok;
    double value = ui->display->text().toDouble(&ok);
    if (ok && value != 0) {
        double result = 1.0 / value;
        ui->display->setText(QString::number(result));
    } else {
        ui->display->setText("Error");
    }
}


void MainWindow::on_percent_pressed()
{
    bool ok;
    double value = ui->display->text().toDouble(&ok);
    if (ok) {
        double result = value / 100.0;
        ui->display->setText(QString::number(result));
    }
}
