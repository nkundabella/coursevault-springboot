#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_1,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_2,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_3,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_4,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_5,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_6,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_7,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_8,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_9,&QPushButton::released,this,&MainWindow::pushed_buttons);
    connect(ui->pushButton_posneg, &QPushButton::released,this,&MainWindow::toggle_sign);
    connect(ui->pushButton_percent, &QPushButton::released,this,&MainWindow::percent_pressed);
    connect(ui->pushButton_CE, &QPushButton::released,this,&MainWindow::ce);
    connect(ui->pushButton_plus,&QPushButton::released,this,&MainWindow::operator_pressed);
    connect(ui->pushButton_minus,&QPushButton::released,this,&MainWindow::operator_pressed);
    connect(ui->pushButton_multi,&QPushButton::released,this,&MainWindow::operator_pressed);
    connect(ui->pushButton_div,&QPushButton::released,this,&MainWindow::operator_pressed);
    connect(ui->pushButton_equal,&QPushButton::released,this,&MainWindow::equal);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::pushed_buttons() {
    QPushButton *button = (QPushButton*)sender();

    if (!type_secnum || ui->label->text() == "0") {
        ui->label->setText(button->text());
        type_secnum = true;
    } else {
        ui->label->setText(ui->label->text() + button->text());
    }
}

void MainWindow::on_pushButton_dot_released()
{
    ui->label->setText(ui->label->text() + ".");
}
void MainWindow::toggle_sign(){
    double labelNum = ui->label->text().toDouble();
    labelNum *=-1;
    QString newlabel = QString::number(labelNum,'g',15);
    ui->label->setText(newlabel);
}
void MainWindow::percent_pressed(){
    double labelNum = ui->label->text().toDouble();
    labelNum = labelNum /100.0;
    QString newlabel = QString::number(labelNum,'g',15);
    ui->label->setText(newlabel);
}
void MainWindow::ce(){
    ui->label->setText("0");
}
void MainWindow::operator_pressed(){
    QPushButton *btn = (QPushButton*)sender();
    QString sign = btn->text();
    double current_num = ui->label->text().toDouble();

    if(!next_operator.isEmpty() && type_secnum){
        if(next_operator == "+")
            fnum +=current_num;
        else if(next_operator == "-")
            fnum -=current_num;
        else if(next_operator == "*")
            fnum *=current_num;
        else if(next_operator == "/"){
            if(current_num == 0.0){
                ui->label->setText("Error");
                next_operator = "";
                return ;
            }
        fnum /=current_num;
        }
     ui->label->setText(QString::number(fnum,'g',15));
    }else{
        fnum = current_num;
    }
    next_operator = sign;
    type_secnum = false;

}
void MainWindow::equal() {
    double lnum = ui->label->text().toDouble();

    if (!next_operator.isEmpty() && type_secnum) {
        if (next_operator == "+")
            fnum += lnum;
        else if (next_operator == "-")
            fnum -= lnum;
        else if (next_operator == "*")
            fnum *= lnum;
        else if (next_operator == "/") {
            if (lnum == 0.0) {
                ui->label->setText("Error");
                next_operator = "";
                return;
            }
            fnum /= lnum;
        }
        ui->label->setText(QString::number(fnum, 'g', 15));
        next_operator = "";
        type_secnum = false;
    }
}

