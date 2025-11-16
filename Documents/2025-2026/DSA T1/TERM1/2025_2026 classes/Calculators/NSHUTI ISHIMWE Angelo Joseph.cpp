#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QDebug>

double nber;
bool fullNber2 = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton0, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton1, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton2, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton3, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton4, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton5, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton6, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton7, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton8, SIGNAL(released()),this,SLOT(buttonPressed()));
    connect(ui->pushButton9, SIGNAL(released()),this,SLOT(buttonPressed()));

    connect(ui->pushButtonInteger, SIGNAL(released()),this,SLOT(unaryOperator()));
    connect(ui->pushButtonPercent, SIGNAL(released()),this,SLOT(unaryOperator()));
    connect(ui->pushButtonCE, SIGNAL(released()),this,SLOT(unaryOperator()));
    connect(ui->pushButtonSquare, SIGNAL(released()),this,SLOT(unaryOperator()));


    connect(ui->pushButtonAdd_2, SIGNAL(released()),this,SLOT(binaryOperator()));
    connect(ui->pushButtonMinus, SIGNAL(released()),this,SLOT(binaryOperator()));
    connect(ui->pushButtonMult, SIGNAL(released()),this,SLOT(binaryOperator()));
    connect(ui->pushButtonDivide, SIGNAL(released()),this,SLOT(binaryOperator()));

    ui->pushButtonDivide->setCheckable(true);
    ui->pushButtonAdd_2->setCheckable(true);
    ui->pushButtonMinus->setCheckable(true);
    ui->pushButtonMult->setCheckable(true);
    ui->pushButtonSquare->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed(){
    QPushButton *button = (QPushButton*)sender();

    double inputs;
    QString expressions;

    if((ui->pushButtonAdd_2->isChecked() || ui->pushButtonMult->isChecked() || ui->pushButtonDivide->isChecked() || ui->pushButtonMult->isChecked() || ui->pushButtonSquare->isChecked()) && (!fullNber2)){
        inputs = button->text().toDouble();
        fullNber2 = true;
        expressions = QString::number(inputs,'g', 15);
    }else{
        if(ui->Input->text().contains('.') && button->text() == "0"){
            expressions = ui->Input->text() +  button->text();
        }else{
             inputs = (ui->Input->text() + button->text()).toDouble();
             expressions = QString::number(inputs,'g', 15);
        }
    }
    ui->Input->setText(expressions);

}

void MainWindow::on_pushButtonDot_released()
{
    ui->Input->setText(ui->Input->text() + ".");
}

void MainWindow::unaryOperator(){
    double inputs;
    QString expressions;

    QPushButton * button = (QPushButton*)sender();
    if(button->text() == "+/-"){
        inputs = ui->Input->text().toDouble();
        inputs = inputs * -1;
        expressions = QString::number(inputs,'g',15);
        ui->Input->setText(expressions);
    }

    if(button->text() == "%"){
        inputs = ui->Input->text().toDouble();
        inputs = inputs * 1/100;
        expressions = QString::number(inputs,'g',15);
        ui->Input->setText(expressions);
    }
    if(ui->pushButtonSquare->isChecked()){
        inputs = ui->Input->text().toDouble();
        inputs = inputs * inputs;
        expressions = QString::number(inputs,'g',15);
        ui->Input->setText(expressions);
    }
}


void MainWindow::on_pushButtonCE_released()
{
    QPushButton *button = (QPushButton*)sender();
    if(button->text() == "CE"){
        ui->Input->setText("0");
    }
}


void MainWindow::on_pushButtonEqual_released()
{
    double input, nber2;
    nber2 = ui->Input->text().toDouble();
    QString expression;
    if(ui->pushButtonAdd_2->isChecked()){
        input = nber + nber2;
        expression = QString::number(input,'g',15);
        ui->Input->setText(expression);
        ui->pushButtonAdd_2->setChecked(false);
    }
    else if(ui->pushButtonDivide->isChecked()){
        if(nber2 == 0){
            expression = "Undefined";
            ui->Input->setText(expression);
        }else{
            input = nber / nber2;
            expression = QString::number(input,'g',15);
            ui->Input->setText(expression);
            ui->pushButtonDivide->setChecked(false);
        }
    }
    else if(ui->pushButtonMinus->isChecked()){
        input = nber - nber2;
        expression = QString::number(input,'g',15);
        ui->Input->setText(expression);
        ui->pushButtonMinus->setChecked(false);
    }
    else if(ui->pushButtonMult->isChecked()){
        input = nber * nber2;
        expression = QString::number(input,'g',15);
        ui->Input->setText(expression);
        ui->pushButtonMult->setChecked(false);
    }

    fullNber2 = false;
}

void MainWindow::binaryOperator(){
    QPushButton *button = (QPushButton*)sender();

    nber = ui->Input->text().toDouble();
    button->setChecked(true);
}

