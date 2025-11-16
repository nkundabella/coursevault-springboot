#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>
#include <QString>
#include <QChar>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString numStyle = "background-color: #87CEFA; color: black; font: bold 14px; "
                       "border-radius: 25px; margin-top: 5px; margin-bottom: 5px;";
    ui->btn0->setStyleSheet(numStyle);
    ui->btn1->setStyleSheet(numStyle);
    ui->btn2->setStyleSheet(numStyle);
    ui->btn3->setStyleSheet(numStyle);
    ui->btn4->setStyleSheet(numStyle);
    ui->btn5->setStyleSheet(numStyle);
    ui->btn6->setStyleSheet(numStyle);
    ui->btn7->setStyleSheet(numStyle);
    ui->btn8->setStyleSheet(numStyle);
    ui->btn9->setStyleSheet(numStyle);

    QString opStyle = "background-color: orange; color: white; font: bold 14px; "
                      "border-radius: 25px; margin-top: 5px; margin-bottom: 5px;";
    ui->btnAdd->setStyleSheet(opStyle);
    ui->btnminus->setStyleSheet(opStyle);
    ui->btnproduct->setStyleSheet(opStyle);
    ui->btndivide->setStyleSheet(opStyle);

    ui->btnequal->setStyleSheet("background-color: green; color: white; font: bold 14px; "
                                "border-radius: 25px; margin-top: 5px; margin-bottom: 5px;");
    ui->btnclear->setStyleSheet("background-color: red; color: white; font: bold 14px; "
                                "border-radius: 25px; margin-top: 5px; margin-bottom: 5px;");

    QString sciStyle = "background-color: #FFA07A; color: white; font: bold 14px; "
                       "border-radius: 25px; margin-top: 5px; margin-bottom: 5px;";
    ui->btnSin->setStyleSheet(sciStyle);
    ui->btnCos->setStyleSheet(sciStyle);
    ui->btnTan->setStyleSheet(sciStyle);
    ui->btnSqr->setStyleSheet(sciStyle);

    ui->display->setStyleSheet("background-color: #F0F0F0; color: black; font: bold 16px; "
                               "border-radius: 8px; height: 40px;");
    ui->display->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ----------------------
// Number buttons
void MainWindow::on_btn0_clicked() { ui->display->setText(ui->display->text() + "0"); }
void MainWindow::on_btn1_clicked() { ui->display->setText(ui->display->text() + "1"); }
void MainWindow::on_btn2_clicked() { ui->display->setText(ui->display->text() + "2"); }
void MainWindow::on_btn3_clicked() { ui->display->setText(ui->display->text() + "3"); }
void MainWindow::on_btn4_clicked() { ui->display->setText(ui->display->text() + "4"); }
void MainWindow::on_btn5_clicked() { ui->display->setText(ui->display->text() + "5"); }
void MainWindow::on_btn6_clicked() { ui->display->setText(ui->display->text() + "6"); }
void MainWindow::on_btn7_clicked() { ui->display->setText(ui->display->text() + "7"); }
void MainWindow::on_btn8_clicked() { ui->display->setText(ui->display->text() + "8"); }
void MainWindow::on_btn9_clicked() { ui->display->setText(ui->display->text() + "9"); }

// ----------------------
// Operator buttons
void MainWindow::on_btnAdd_clicked()     { ui->display->setText(ui->display->text() + "+"); }
void MainWindow::on_btnminus_clicked()   { ui->display->setText(ui->display->text() + "-"); }
void MainWindow::on_btnproduct_clicked() { ui->display->setText(ui->display->text() + "*"); }
void MainWindow::on_btndivide_clicked()  { ui->display->setText(ui->display->text() + "/"); }

// ----------------------
// Equal button
void MainWindow::on_btnequal_clicked()
{
    QString expr = ui->display->text();
    if(expr.isEmpty()) return;

    double result = evaluateExpression(expr);
    ui->display->setText(QString::number(result));
}

// ----------------------
// Clear button
void MainWindow::on_btnclear_clicked()
{
    ui->display->clear();
}

// ----------------------
// Scientific buttons
void MainWindow::on_btnSin_clicked() {
    double val = ui->display->text().toDouble();
    double radians = qDegreesToRadians(val);   // convert degrees to radians
    ui->display->setText(QString::number(qSin(radians)));
}

void MainWindow::on_btnCos_clicked() {
    double val = ui->display->text().toDouble();
    double radians = qDegreesToRadians(val);   // convert degrees to radians
    ui->display->setText(QString::number(qCos(radians)));
}

void MainWindow::on_btnTan_clicked() {
    double val = ui->display->text().toDouble();
    double radians = qDegreesToRadians(val);   // convert degrees to radians
    ui->display->setText(QString::number(qTan(radians)));
}

void MainWindow::on_btnSqr_clicked() {
    double val = ui->display->text().toDouble();
    ui->display->setText(QString::number(val * val));
}

// ----------------------
// Expression evaluator
double MainWindow::evaluateExpression(const QString &expr)
{
    std::stack<double> numbers;
    std::stack<QChar> ops;
    QString numStr;

    auto applyOp = [](double a, double b, QChar op) -> double {
        if(op == '+') return a + b;
        if(op == '-') return a - b;
        if(op == '*') return a * b;
        if(op == '/') return b != 0 ? a / b : 0;
        return 0;
    };

    for(int i=0; i<expr.length(); ++i){
        QChar ch = expr[i];
        if(ch.isDigit() || ch == '.'){
            numStr += ch;
        } else if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
            numbers.push(numStr.toDouble());
            numStr.clear();

            while(!ops.empty() &&
                   ((ops.top() == '*' || ops.top() == '/') || (ch == '+' || ch == '-'))){
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                QChar op = ops.top(); ops.pop();
                numbers.push(applyOp(a,b,op));
            }
            ops.push(ch);
        }
    }

    if(!numStr.isEmpty())
        numbers.push(numStr.toDouble());

    while(!ops.empty()){
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        QChar op = ops.top(); ops.pop();
        numbers.push(applyOp(a,b,op));
    }

    return numbers.top();
}
