#ifndef NKUNDAISABELLA_H
#define NKUNDAISABELLA_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;  

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    QString pendingOperator;
    double pendingOperand = 0;
    bool waitingForOperand = true;

    void handleInput(const QString &text);  
    void abortOperation();
    bool calculate(double rightOperand, const QString &operatorText);
};

#endif