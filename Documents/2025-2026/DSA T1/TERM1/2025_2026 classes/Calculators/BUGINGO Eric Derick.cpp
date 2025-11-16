#include "mainwindow.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), lastPressedEqual(false), angleMode(DEG)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);
    display->setStyleSheet("font-size: 24px;");
    mainLayout->addWidget(display);

    layout = new QGridLayout();
    mainLayout->addLayout(layout);

    createButtons();
}

MainWindow::~MainWindow() {}

void MainWindow::createButtons()
{
    // Digits + operators
    QString buttons[5][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"},
        {"C", "mod", "sin", "cos"}
    };

    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<4; ++j)
        {
            if(buttons[i][j].isEmpty()) continue;

            QPushButton *button = new QPushButton(buttons[i][j]);
            button->setFixedSize(60,60);
            button->setStyleSheet("font-size: 18px;");
            layout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
        }
    }

    // Extra row for tan
    QPushButton *tanBtn = new QPushButton("tan");
    tanBtn->setFixedSize(60,60);
    tanBtn->setStyleSheet("font-size: 18px;");
    layout->addWidget(tanBtn, 5, 0);
    connect(tanBtn, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // Angle mode buttons (DEG, RAD, GRAD)
    modeGroup = new QButtonGroup(this);

    QPushButton *degBtn = new QPushButton("DEG");
    QPushButton *radBtn = new QPushButton("RAD");
    QPushButton *gradBtn = new QPushButton("GRAD");

    degBtn->setCheckable(true);
    radBtn->setCheckable(true);
    gradBtn->setCheckable(true);

    modeGroup->addButton(degBtn, DEG);
    modeGroup->addButton(radBtn, RAD);
    modeGroup->addButton(gradBtn, GRAD);

    layout->addWidget(degBtn, 5, 1);
    layout->addWidget(radBtn, 5, 2);
    layout->addWidget(gradBtn, 5, 3);

    // Default = DEG (green)
    degBtn->setChecked(true);
    degBtn->setStyleSheet("background-color: green; color: white; font-weight: bold;");

    connect(modeGroup, &QButtonGroup::idClicked,
            this, &MainWindow::onModeChanged);
}

void MainWindow::onModeChanged(int id)
{
    angleMode = static_cast<AngleMode>(id);

    // Reset styles
    for(auto *btn : modeGroup->buttons())
        btn->setStyleSheet("font-size: 18px;");

    // Highlight active
    QPushButton *activeBtn = qobject_cast<QPushButton*>(modeGroup->button(id));
    if(activeBtn)
        activeBtn->setStyleSheet("background-color: green; color: white; font-weight: bold;");
}

void MainWindow::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString text = button->text();

    if(text == "C") // Clear all
    {
        currentExpression.clear();
        display->setText("0");
        lastPressedEqual = false;
    }
    else if(text == "=")
    {
        if(currentExpression.isEmpty()) return;

        double result = calculateExpression(currentExpression);
        display->setText(QString::number(result));
        currentExpression = QString::number(result);
        lastPressedEqual = true;
    }
    else if(text == "sin" || text == "cos" || text == "tan")
    {
        if(currentExpression.isEmpty()) return;
        double value = currentExpression.toDouble();
        double result = applyTrigFunction(text, value);

        display->setText(QString::number(result));
        currentExpression = QString::number(result);
        lastPressedEqual = true;
    }
    else
    {
        // Map "mod" button press to "%" for internal expression
        QString appendText = (text == "mod") ? "%" : text;
        appendToExpression(appendText);
    }
}

void MainWindow::appendToExpression(const QString &text)
{
    if(lastPressedEqual)
    {
        currentExpression.clear();
        lastPressedEqual = false;
    }

    if(currentExpression == "0" && text != ".") currentExpression.clear();

    currentExpression += text;
    display->setText(currentExpression);
}

double MainWindow::calculateExpression(const QString &expr)
{
    double result = 0;
    if(expr.contains('+'))
    {
        QStringList parts = expr.split('+');
        result = parts[0].toDouble() + parts[1].toDouble();
    }
    else if(expr.contains('-'))
    {
        QStringList parts = expr.split('-');
        result = parts[0].toDouble() - parts[1].toDouble();
    }
    else if(expr.contains('*'))
    {
        QStringList parts = expr.split('*');
        result = parts[0].toDouble() * parts[1].toDouble();
    }
    else if(expr.contains('/'))
    {
        QStringList parts = expr.split('/');
        if(parts[1].toDouble() != 0)
            result = parts[0].toDouble() / parts[1].toDouble();
        else
        {
            display->setText("Error");
            result = 0; // Handle division by zero
        }
    }
    else if(expr.contains('%'))
    {
        QStringList parts = expr.split('%');
        double divisor = parts[1].toDouble();
        if(divisor != 0 && qFloor(parts[0].toDouble()) == parts[0].toDouble() && qFloor(divisor) == divisor)
        {
            // Ensure inputs are integers for modulo
            result = static_cast<int>(parts[0].toDouble()) % static_cast<int>(divisor);
        }
        else
        {
            display->setText("Error"); // Display error for invalid modulo
            result = 0;
        }
    }
    else
    {
        result = expr.toDouble();
    }
    return result;
}

double MainWindow::applyTrigFunction(const QString &func, double value)
{
    double rad = value;
    if(angleMode == DEG)
        rad = qDegreesToRadians(value);
    else if(angleMode == GRAD)
        rad = value * M_PI / 200.0;

    if(func == "sin") return qSin(rad);
    if(func == "cos") return qCos(rad);
    if(func == "tan") return qTan(rad);

    return 0;
}
