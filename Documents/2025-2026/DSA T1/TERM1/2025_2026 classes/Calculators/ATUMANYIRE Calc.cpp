#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QToolButton>
#include <QStack>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Number buttons 0-9
    QList<QToolButton*> numButtons = {
        ui->numberButton_35, ui->numberButton_31, ui->numberButton_32,
        ui->numberButton_30, ui->numberButton_27, ui->numberButton_28,
        ui->numberButton_26, ui->numberButton_22, ui->numberButton_23,
        ui->numberButton_24
    };

    for (int i = 0; i <= 9; ++i) {
        connect(numButtons[i], &QToolButton::clicked, [=](){
            ui->display->insert(QString::number(i));
        });
    }

    // Operator buttons
    connect(ui->numberButton_18, &QToolButton::clicked, [=](){ ui->display->insert("÷"); });
    connect(ui->numberButton_21, &QToolButton::clicked, [=](){ ui->display->insert("×"); });
    connect(ui->numberButton_25, &QToolButton::clicked, [=](){ ui->display->insert("-"); });
    connect(ui->numberButton_29, &QToolButton::clicked, [=](){ ui->display->insert("+"); });

    // Clear buttons
    connect(ui->numberButton_19, &QToolButton::clicked, [=](){ ui->display->clear(); }); // AC
    connect(ui->numberButton_20, &QToolButton::clicked, [=](){
        QString text = ui->display->text();
        text.chop(1);
        ui->display->setText(text);
    }); // C

    // Square root
    connect(ui->numberButton_34, &QToolButton::clicked, [=](){
        bool ok;
        double val = ui->display->text().toDouble(&ok);
        if(ok) ui->display->setText(QString::number(sqrt(val)));
    });

    // Square
    connect(ui->numberButton_36, &QToolButton::clicked, [=](){
        bool ok;
        double val = ui->display->text().toDouble(&ok);
        if(ok) ui->display->setText(QString::number(val*val));
    });

    // Equal button
    connect(ui->numberButton_33, &QToolButton::clicked, [=](){
        QString expr = ui->display->text();
        double result = calculateExpression(expr);
        ui->display->setText(QString::number(result));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Simple evaluator: handles + - * / with left-to-right (no precedence)
double MainWindow::calculateExpression(const QString &expr)
{
    QString exp = expr;
    exp.replace("×", "*");  // Convert display symbol to operator
    exp.replace("÷", "/");  // Convert display symbol to operator

    double result = 0;
    double num = 0;
    QChar op = '+';
    QString temp = "";

    for(int i=0; i<exp.length(); ++i) {
        QChar c = exp[i];
        if(c.isDigit() || c=='.') {
            temp += c;
        }
        if(!c.isDigit() && c!='.' || i==exp.length()-1) {
            if(!temp.isEmpty()) num = temp.toDouble();
            temp = "";

            switch(op.unicode()) {
            case '+': result += num; break;
            case '-': result -= num; break;
            case '*': result *= num; break;
            case '/': result /= num; break;
            }
            op = c;
        }
    }

    return result;
}
