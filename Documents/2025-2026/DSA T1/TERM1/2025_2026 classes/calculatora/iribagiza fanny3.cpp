#include "calculator.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>

class CalculatorGUI : public QWidget {
    Q_OBJECT
    QLineEdit *display;
    double firstNum;
    char op;
public:
    CalculatorGUI() {
        display = new QLineEdit();
        QGridLayout *layout = new QGridLayout(this);

        
        QPushButton *buttons[10];
        for(int i=0; i<=9; i++){
            buttons[i] = new QPushButton(QString::number(i));
            int row = 3 - (i-1)/3;
            int col = (i-1)%3;
            if(i==0) layout->addWidget(buttons[i], 4, 0, 1, 3);
            else layout->addWidget(buttons[i], row, col);
            connect(buttons[i], &QPushButton::clicked, this, [=](){
                display->setText(display->text() + QString::number(i));
            });
        }

        
        QPushButton *btnAdd = new QPushButton("+");
        QPushButton *btnSub = new QPushButton("-");
        QPushButton *btnMul = new QPushButton("*");
        QPushButton *btnDiv = new QPushButton("/");
        QPushButton *btnEqual = new QPushButton("=");
        layout->addWidget(btnAdd, 1, 3);
        layout->addWidget(btnSub, 2, 3);
        layout->addWidget(btnMul, 3, 3);
        layout->addWidget(btnDiv, 4, 3);
        layout->addWidget(btnEqual, 4, 4);
        layout->addWidget(display, 0, 0, 1, 5);

        auto setOperator = [&](char oper){
            firstNum = display->text().toDouble();
            op = oper;
            display->clear();
        };

        connect(btnAdd, &QPushButton::clicked, this, [=](){ setOperator('+'); });
        connect(btnSub, &QPushButton::clicked, this, [=](){ setOperator('-'); });
        connect(btnMul, &QPushButton::clicked, this, [=](){ setOperator('*'); });
        connect(btnDiv, &QPushButton::clicked, this, [=](){ setOperator('/'); });

        connect(btnEqual, &QPushButton::clicked, this, [=](){
            double secondNum = display->text().toDouble();
            double result = 0;
            switch(op){
                case '+': result = add(firstNum, secondNum); break;
                case '-': result = subtract(firstNum, secondNum); break;
                case '*': result = multiply(firstNum, secondNum); break;
                case '/': result = divide(firstNum, secondNum); break;
            }
            display->setText(QString::number(result));
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CalculatorGUI window;
    window.show();
    return app.exec();
}
