#include "NIYONKURU_Gloria.h"
#include "ui_NIYONKURU_Gloria.h"
#include <QPushButton>
#include <QJSEngine>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QRegularExpression regex("[0-9+\\-*/.]*");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->display->setValidator(validator);

    // Connect number buttons (0-9)
    QPushButton* numButtons[10] = {ui->button0, ui->button1, ui->button2, ui->button3,
                                   ui->button4, ui->button5, ui->button6, ui->button7,
                                   ui->button8, ui->button9};

    for(int i = 0; i < 10; ++i){
        connect(numButtons[i], &QPushButton::clicked, this, &MainWindow::digit_pressed);
    }
    connect(ui->dotButton, &QPushButton::clicked, this, &MainWindow::dot_pressed);

    // Connect operator buttons (+ - * /)
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::math_operator_pressed);
    connect(ui->subButton, &QPushButton::clicked, this, &MainWindow::math_operator_pressed);
    connect(ui->mulButton, &QPushButton::clicked, this, &MainWindow::math_operator_pressed);
    connect(ui->divButton, &QPushButton::clicked, this, &MainWindow::math_operator_pressed);

    // Connect equals, clear, delete
    connect(ui->equalButton, &QPushButton::clicked, this, &MainWindow::equals_pressed);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clear_pressed);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::delete_pressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Number buttons clicked
void MainWindow::digit_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    ui->display->insert(button->text());
}

// Decimal point button clicked
void MainWindow::dot_pressed()
{
    ui->display->insert(".");
}

// Operator button clicked (+ - * /)
void MainWindow::math_operator_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    ui->display->insert(button->text());
}

// Equals button clicked (evaluate full expression with BODMAS)
void MainWindow::equals_pressed()
{
    QString expression = ui->display->text();

    QJSEngine engine;
    QJSValue result = engine.evaluate(expression);

    if (result.isError()) {
        ui->display->setText("Error");
    } else {
        ui->display->setText(result.toString());
    }
}

// Clear button clicked
void MainWindow::clear_pressed()
{
    ui->display->clear();
}

// Delete (backspace) button clicked
void MainWindow::delete_pressed()
{
    QString text = ui->display->text();
    text.chop(1);  // remove last character
    ui->display->setText(text);
}
