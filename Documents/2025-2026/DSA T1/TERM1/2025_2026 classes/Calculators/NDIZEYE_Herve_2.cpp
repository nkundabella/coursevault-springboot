#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QString>
#include <QChar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,pendingOperand(0.0)
    ,waitingForOperand(true)
{
    ui->setupUi(this);
    for(int i = 0;i <=9; ++i){
        QString buttonName = "pushButton_" + QString::number(i);
        QPushButton *button = findChild<QPushButton *>(buttonName);
        if(button){
            connect(button, &QPushButton::clicked, this, &MainWindow::digitPressed);
        }
    }
    connect(ui->pushButton_add, &QPushButton::clicked, this, &MainWindow::operatorPressed);
    connect(ui->pushButton_min, &QPushButton::clicked, this, &MainWindow::operatorPressed);
    connect(ui->pushButton_mult, &QPushButton::clicked, this, &MainWindow::operatorPressed);
    connect(ui->pushButton_div, &QPushButton::clicked, this, &MainWindow::operatorPressed);

    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::clearPressed);
    connect(ui->pushButton_equal, &QPushButton::clicked, this, &MainWindow::equalPressed);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digitPressed()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString digitValue = clickedButton->text();
    QString currentText = ui->lineEdit->text();

    ui->lineEdit->setText(currentText + digitValue);
}
void MainWindow::operatorPressed()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString operatorText = clickedButton->text();
    QString currentText = ui->lineEdit->text();

    // Append operator with spaces for clarity
    ui->lineEdit->setText(currentText + operatorText);
}

void MainWindow::clearPressed()
{
    pendingOperand = 0.0;
    pendingOperator.clear();
    ui->lineEdit->clear();
    waitingForOperand = true;
}
void MainWindow::equalPressed()
{
    QString expr = ui->lineEdit->text();
    double result = 0.0;
    QChar op;
    double left = 0.0;
    double right = 0.0;

    // Simple parser: find operator
    for (int i = 0; i < expr.length(); ++i) {
        QChar c = expr[i];
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            op = c;
            left = expr.left(i).toDouble();
            right = expr.mid(i+1).toDouble();
            break;
        }
    }

    if (op == '+') result = left + right;
    else if (op == '-') result = left - right;
    else if (op == '*') result = left * right;
    else if (op == '/') {
        if (right != 0.0) result = left / right;
        else {
            ui->lineEdit->setText("Error");
            return;
        }
    }

    ui->lineEdit->setText(QString::number(result));
}
