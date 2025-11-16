#include "calculator.h"
#include <QVBoxLayout>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), firstOperand(0),  waitingForOperand(false) {

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    QGridLayout *layout = new QGridLayout;

    QStringList buttons = {
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0",".","=","+"
    };

    int pos = 0;
    for(int row = 0; row < 4 ; ++row){
        for(int col = 0 ; col < 4; ++col){
            QPushButton *button = new QPushButton(buttons[pos]);
            button ->setFixedSize(50,50);
            layout->addWidget(button,row,col);
            connect(button,&QPushButton::clicked, this ,&Calculator::onButtonClicked);
            pos++;
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);
    mainLayout->addLayout(layout);
    setLayout(mainLayout);

    setWindowTitle("Calculator");
}
void Calculator::onButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString clickedText = clickedButton->text();

    if(clickedText== "="){
        double secondOperand = display->text().toDouble();
        if(pendingOperation == "+") firstOperand += secondOperand;
        else if(pendingOperation == "-") firstOperand -= secondOperand;
        else if(pendingOperation == "*") firstOperand *= secondOperand;
        else if (pendingOperation == "/") {
            if(secondOperand !=0) firstOperand /= secondOperand;
            else display->setText("Error");
        }
        display->setText(QString::number(firstOperand));
        pendingOperation.clear();
        waitingForOperand = true;
    }
    else if(clickedText == "+" || clickedText == "-" || clickedText == "*" || clickedText == "/"){
        pendingOperation = clickedText;
        firstOperand = display ->text().toDouble();
        waitingForOperand = true;
     }
    else {
    if(display->text()== "0" || waitingForOperand){
        display ->clear();
        waitingForOperand = false;
    }
    display->setText(display->text()+ clickedText);
   }
}
