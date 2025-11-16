#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0:
        ui->pushButton_zero->click();
        break;
    case Qt::Key_1:
        ui->pushButton_one->click();
        break;
    case Qt::Key_2:
        ui->pushButton_two->click();
        break;
    case Qt::Key_3:
        ui->pushButton_three->click();
        break;
    case Qt::Key_4:
        ui->pushButton_four->click();
        break;
    case Qt::Key_5:
        ui->pushButton_five->click();
        break;
    case Qt::Key_6:
        ui->pushButton_six->click();
        break;
    case Qt::Key_7:
        ui->pushButton_seven->click();
        break;
    case Qt::Key_8:
        ui->pushButton_eight->click();
        break;
    case Qt::Key_9:
        ui->pushButton_nine->click();
        break;

    case Qt::Key_Plus:
        ui->pushButton_plus->click();
        break;
    case Qt::Key_Minus:
        ui->pushButton_minus->click();
        break;
    case Qt::Key_Asterisk:
        ui->pushButton_multiply->click();
        break;
    case Qt::Key_Slash:
        ui->pushButton_divide->click();
        break;

    case Qt::Key_Equal:
    case Qt::Key_Return:
    case Qt::Key_Enter:
        ui->pushButton_equal->click();
        break;

    case Qt::Key_Delete:
        ui->pushButton_delete->click();
        break;

    case Qt::Key_Backspace:
        ui->pushButton_delete->click();
        break;

    case Qt::Key_Shift:
        ui->pushButton_root->click();
        break;

    default:
        QMainWindow::keyPressEvent(event);
    }
}

double firstNum;
double memoryValue = 0;
bool userIsTypingSecondnumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_zero,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_one,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_two,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_three,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_four,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_five,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_six,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_seven,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_eight,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_nine,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digit_pressed(){

    QPushButton *button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() || ui->pushButton_multiply->isChecked() ||ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber)){
        labelNumber = button->text().toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber,'g',15);
    }else{
        if(ui->label->text().contains('.')&& button->text() == "0"){
            newLabel = ui->label->text()+ button->text();
        }
        else{
            labelNumber = (ui->label->text()+button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g',15);
        }
        labelNumber = (ui->label->text() + button->text()).toDouble();
    }

    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_dot_released()
{
    ui->label->setText(ui->label->text() + ".");
}
void MainWindow::on_pushButton_percentage_released()
{
    double value = ui->label->text().toDouble();
    value = value / 100.0;
    ui->label->setText(QString::number(value, 'g', 15));
}
void MainWindow::on_pushButton_plusnminus_released()
{
    double labelNumber = ui->label->text().toDouble();
    labelNumber = labelNumber * -1;
    QString newLabel = QString::number(labelNumber, 'g', 15);
    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_delete_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label->setText("0");
}


void MainWindow::on_pushButton_equal_released()
{

    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();


    if(ui->pushButton_plus->isChecked()){
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }

    else if(ui->pushButton_minus->isChecked()){
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }

    else if(ui->pushButton_multiply->isChecked()){
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);
    }

    else if(ui->pushButton_divide->isChecked()){
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }

    else if (ui->pushButton_high->isChecked()) {
        labelNumber = qPow(firstNum, secondNum);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_high->setChecked(false);
    }
    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed(){
    QPushButton *button = (QPushButton*)sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}

void MainWindow::on_pushButton_root_released()
{
    double value = ui->label->text().toDouble();
    if (value >= 0) {
        value = qSqrt(value);
        ui->label->setText(QString::number(value, 'g', 15));
    } else {
        ui->label->setText("Error");
    }
}

void MainWindow::on_pushButton_powernegative_released()
{
    double value = ui->label->text().toDouble();
    if (value != 0) {
        value = 1.0 / value;
        ui->label->setText(QString::number(value, 'g', 15));
    } else {
        ui->label->setText("Error");
    }
}

void MainWindow::on_pushButton_tan_released()
{
    double value = ui->label->text().toDouble();
    value = qTan(value);
    ui->label->setText(QString::number(value, 'g', 15));
}

void MainWindow::on_pushButton_power2_released()
{
    double value = ui->label->text().toDouble();
    value = value * value;
    ui->label->setText(QString::number(value, 'g', 15));
}

void MainWindow::on_pushButton_high_released(){
    firstNum = ui->label->text().toDouble();
    ui->pushButton_high->setChecked(true);
}

void MainWindow::on_pushButton_in_released(){
    double value = ui->label->text().toDouble();
    if (value > 0) {
        value = qLn(value);
        ui->label->setText(QString::number(value, 'g', 15));
    } else {
        ui->label->setText("Error");
    }
}

void MainWindow::on_pushButton_sin_released(){
    double value = ui->label->text().toDouble();
    value = qSin(value);
    ui->label->setText(QString::number(value, 'g',15));
}

void MainWindow::on_pushButton_cos_released()
{
    double value = ui->label->text().toDouble();
    value = qCos(value);
    ui->label->setText(QString::number(value, 'g', 15));
}

void MainWindow::on_pushButton_closeb_released()
{
    ui->label->setText(ui->label->text() + "(");
}

void MainWindow::on_pushButton_bracket_released()
{
    ui->label->setText(ui->label->text() + ")");
}

void MainWindow::on_pushButton_exp_released()
{
    ui->label->setText(ui->label->text() + "E");
}

void MainWindow::on_pushButton_bslashc_released()
{
    QString text = ui->label->text();
    text.chop(1); // remove last char
    if (text.isEmpty()) {
        text = "0";
    }
    ui->label->setText(text);
}

void MainWindow::on_pushButton_rcl_released()
{
    ui->label->setText(QString::number(memoryValue, 'g', 15));
}

void MainWindow::on_pushButton_store_released()
{
    memoryValue = ui->label->text().toDouble();
}







