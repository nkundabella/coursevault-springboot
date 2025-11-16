#include "UmurerwaBonnette.h"
#include "ui_UmurerwaBonnette2.h"
#include <QDebug>
#include <QPushButton>

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_plusminus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiplication, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));


    connect(ui->pushButton_dot, SIGNAL(released()), this, SLOT(on_pushButton__released()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString newLabel;

    if ((ui->pushButton_add->isChecked() || ui->pushButton_minus->isChecked()
         || ui->pushButton_multiplication->isChecked() || ui->pushButton_divide->isChecked())
        && userIsTypingSecondNumber) {

        newLabel = button->text();
        userIsTypingSecondNumber = false;
    } else {
        QString currentText = ui->label->text();
        if (currentText == "0") {
            newLabel = button->text();
        } else {
            newLabel = currentText + button->text();
        }
    }

    ui->label->setText(newLabel);
    qDebug() << "Pressed:" << button->text() << "-> Current label:" << newLabel;
}
void MainWindow::on_pushButton__released() {
    QString currentText = ui->label->text();

    if (userIsTypingSecondNumber) {
        ui->label->setText("0.");
        userIsTypingSecondNumber = false;
        return;
    }

    if (!currentText.contains(".")) {
        if (currentText.isEmpty() || currentText == "0") {
            ui->label->setText("0.");
        } else {
            ui->label->setText(currentText + ".");
        }
    }

    qDebug() << "Decimal added -> Current label:" << ui->label->text();
}

void MainWindow::unary_operation_pressed() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    double labelNumber;
    QString newLabel;

    if (button->text() == "+/-") {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if (button->text() == "%") {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::on_pushButton_clear_released() {
    ui->label->setText("0");
    firstNum = 0;
    userIsTypingSecondNumber = false;

    ui->pushButton_add->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiplication->setChecked(false);
    ui->pushButton_divide->setChecked(false);
}

void MainWindow::on_pushButton_equal_released() {
    double labelNumber, secondNum;
    QString newLabel;
    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_add->isChecked()) {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    } else if(ui->pushButton_minus->isChecked()) {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    } else if(ui->pushButton_multiplication->isChecked()) {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_multiplication->setChecked(false);
    } else if(ui->pushButton_divide->isChecked()) {
        if (secondNum == 0) {
            ui->label->setText("Error");
        } else {
            labelNumber = firstNum / secondNum;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label->setText(newLabel);
        }
        ui->pushButton_divide->setChecked(false);
    }
}

void MainWindow::binary_operation_pressed() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    firstNum = ui->label->text().toDouble();
    button->setChecked(true);
    userIsTypingSecondNumber = true;
}
