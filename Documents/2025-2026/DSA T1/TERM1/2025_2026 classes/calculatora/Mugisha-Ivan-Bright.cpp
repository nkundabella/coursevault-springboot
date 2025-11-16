 #include "Mugisha-Ivan-Bright.h"
#include "./ui_Mugisha-Ivan-Bright.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_period,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_add,SIGNAL(released()), this, SLOT(operation_pressed()));
    connect(ui->pushButton_minus,SIGNAL(released()), this, SLOT(operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()), this, SLOT(operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()), this, SLOT(operation_pressed()));


    connect(ui->pushButton_equal,SIGNAL(released()), this, SLOT(equals_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

    connect(ui->pushButton_clearAll, SIGNAL(released()), this, SLOT(clear_pressed()));
    connect(ui->pushButton_clearAll_2, SIGNAL(released()), this, SLOT(clear_pressed()));
    connect(ui->pushButton_clear, SIGNAL(released()), this, SLOT(backspace_pressed()));

    connect(ui->pushButton_square, SIGNAL(released()), this, SLOT(square_pressed()));

    connect(ui->pushButton_sqrt, SIGNAL(released()), this, SLOT(sqrt_pressed()));

    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(percent_pressed()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton *)sender();

    if(!button) return;


    QString buttonValue = button->text();
    QString currentText = ui->label->text();

    if(currentText == "0" || UserIsTypingSecondNum || result_logged){
        ui->label->setText(buttonValue);
        UserIsTypingSecondNum = false;
        result_logged = false;

    }
    else
    ui->label->setText(currentText + buttonValue);
}

void MainWindow::operation_pressed(){

    QPushButton * button = (QPushButton*)sender();
    if(!button) {return;
        printf("Failed to add operation");
    }

    firstNum = ui->label->text().toDouble();
    UserIsTypingSecondNum = true;
    button->setChecked(true);
}



void MainWindow::equals_pressed() {

    double secondNum = ui->label->text().toDouble();

    QString result;

    if(ui->pushButton_add->isChecked()){
        result = QString::number(firstNum + secondNum, 'g', 15);
        ui->pushButton_add->setChecked(false);
    }else if(ui->pushButton_divide->isChecked()){
        if(secondNum == 0) {
            result = "Error";
        }else{
            result = QString::number(firstNum / secondNum, 'g', 15);
            ui->pushButton_divide->setChecked(false);
        }

    }else if(ui->pushButton_multiply->isChecked()){
        result = QString::number(firstNum * secondNum, 'g', 15);
    ui->pushButton_multiply->setChecked(false);
    }else if(ui->pushButton_minus->isChecked()){
        result = QString::number(firstNum - secondNum, 'g', 15);
      ui->pushButton_minus->setChecked(false);
    }else{
        result = ui->label->text();
    }

    ui->label->setText(result);
    result_logged = true;
}



void MainWindow::clear_pressed() {
    ui->label->setText("0");
    firstNum = 0;
    UserIsTypingSecondNum = false;
    result_logged = false;

    ui->pushButton_add->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
}



void MainWindow::backspace_pressed() {
    QString currentText = ui->label->text();

    if(result_logged){
        ui->label->setText("0");
    }
    if(currentText.length() > 1) {
        currentText.chop(1);
    } else {
        currentText = "0";
    }

    ui->label->setText(currentText);
}

void MainWindow::square_pressed() {
    double num = ui->label->text().toDouble();
    double result = num * num;
    ui->label->setText(QString::number(result, 'g', 15));
    result_logged = true;
}

void MainWindow::sqrt_pressed() {
    double num = ui->label->text().toDouble();
    if(num < 0) {
        ui->label->setText("Error");
    } else {
        double result = sqrt(num);
        ui->label->setText(QString::number(result, 'g', 15));
    }
    result_logged = true;
}

void MainWindow::percent_pressed() {
    double num = ui->label->text().toDouble();

    num = num / 100.0;

    ui->label->setText(QString::number(num, 'g', 15));
    result_logged = true;
}




