#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>

class Calculator : public QWidget {
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onDigit();
    void onOperator();
    void onEquals();
    void onClear();

private:
    QLineEdit *display;
    QString op;
    double num1;
    bool waiting;
};

Calculator::Calculator(QWidget *parent) : QWidget(parent), num1(0), waiting(false) {
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    QGridLayout *layout = new QGridLayout;

    // Digits
    int n = 1;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            QPushButton *b = new QPushButton(QString::number(n++));
            layout->addWidget(b,i,j);
            connect(b,&QPushButton::clicked,this,&Calculator::onDigit);
        }
    QPushButton *b0 = new QPushButton("0");
    layout->addWidget(b0,3,1);
    connect(b0,&QPushButton::clicked,this,&Calculator::onDigit);

    // Operators
    QStringList ops = {"+","-","*","/","=","C"};
    int row=0;
    for(auto s : ops){
        QPushButton *b = new QPushButton(s);
        layout->addWidget(b,row,3);
        if(s=="=") connect(b,&QPushButton::clicked,this,&Calculator::onEquals);
        else if(s=="C") connect(b,&QPushButton::clicked,this,&Calculator::onClear);
        else connect(b,&QPushButton::clicked,this,&Calculator::onOperator);
        row++;
    }

    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(display);
    main->addLayout(layout);
    setLayout(main);
    setWindowTitle("Calculator");
}

void Calculator::onDigit() {
    QPushButton *b = qobject_cast<QPushButton*>(sender());
    if(waiting) { display->setText(b->text()); waiting=false; }
    else display->setText(display->text()=="0"?b->text():display->text()+b->text());
}

void Calculator::onOperator() {
    QPushButton *b = qobject_cast<QPushButton*>(sender());
    op = b->text();
    num1 = display->text().toDouble();
    waiting = true;
}

void Calculator::onEquals() {
    double num2 = display->text().toDouble();
    double result = 0;
    if(op=="+") result = num1+num2;
    else if(op=="-") result = num1-num2;
    else if(op=="*") result = num1*num2;
    else if(op=="/") result = num1/num2;
    display->setText(QString::number(result));
    waiting = true;
}

void Calculator::onClear() {
    display->setText("0");
    num1=0; op=""; waiting=false;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}

#include "main.moc"
