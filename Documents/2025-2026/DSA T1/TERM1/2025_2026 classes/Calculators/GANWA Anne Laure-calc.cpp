#include "GANWA Anne Laure.h"
#include "./ui_GANWA Anne Laure.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- Display ---
    displayLbl = new QLabel("0");
    displayLbl->setAlignment(Qt::AlignRight);
    displayLbl->setFixedHeight(50);

    // --- Button labels ---
    QStringList buttonList = {"7","8","9","4","5","6","1","2","3","0"};
    QStringList buttonFunctions = {"÷","x","-","+"};

    // --- Layouts ---
    QVBoxLayout *vbNumbers = new QVBoxLayout();   // Numbers layout
    QVBoxLayout *vbOperators = new QVBoxLayout(); // Operators + = + C
    QHBoxLayout *hbRows = new QHBoxLayout();      // Horizontal layout for numbers + operators
    QHBoxLayout *hbRow = nullptr;                // Temporary row for numbers

    // --- Number buttons ---
    for(int i=0; i<buttonList.size(); ++i){
        if(i%3 == 0){
            hbRow = new QHBoxLayout();
            vbNumbers->addLayout(hbRow);
        }
        QPushButton *num = new QPushButton(buttonList.at(i));
        num->setFixedSize(50,50);

        connect(num, &QPushButton::clicked, [this,num](){
            if(displayLbl->text() == "0" || waitingForSecondNumber){
                displayLbl->setText(num->text());
                waitingForSecondNumber = false;
            } else {
                displayLbl->setText(displayLbl->text() + num->text());
            }
        });

        hbRow->addWidget(num);
    }

    // --- Operator buttons ---
    for(int k=0; k<buttonFunctions.size(); ++k){
        QPushButton *op = new QPushButton(buttonFunctions.at(k));
        op->setFixedSize(50,50);
        vbOperators->addWidget(op);

        connect(op, &QPushButton::clicked, [this,op](){
            firstNumber = displayLbl->text().toDouble();
            pendingOperator = op->text();
            waitingForSecondNumber = true;
        });
    }

    // --- Equals and Clear ---
    QPushButton *equals = new QPushButton("=");
    equals->setFixedSize(50,50);
    vbOperators->addWidget(equals);

    connect(equals, &QPushButton::clicked, [this](){
        double secondNumber = displayLbl->text().toDouble();
        double result = 0;

        if(pendingOperator == "+") result = firstNumber + secondNumber;
        else if(pendingOperator == "-") result = firstNumber - secondNumber;
        else if(pendingOperator == "x") result = firstNumber * secondNumber;
        else if(pendingOperator == "÷")
            result = (secondNumber != 0) ? firstNumber / secondNumber : 0;

        displayLbl->setText(QString::number(result));
        waitingForSecondNumber = true;
    });

    QPushButton *clear = new QPushButton("C");
    clear->setFixedSize(50,50);
    vbOperators->addWidget(clear);

    connect(clear, &QPushButton::clicked, [this](){
        displayLbl->setText("0");
        firstNumber = 0;
        pendingOperator.clear();
        waitingForSecondNumber = false;
    });

    // --- Combine layouts ---
    hbRows->addLayout(vbNumbers);
    hbRows->addLayout(vbOperators);

    ui->verticalLayout->addWidget(displayLbl);
    ui->verticalLayout->addLayout(hbRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}
