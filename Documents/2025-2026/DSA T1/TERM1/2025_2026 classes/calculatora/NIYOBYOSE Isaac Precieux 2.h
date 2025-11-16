#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QStack>
#include <QKeyEvent>
#include <QMap>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void clearAll();
    void clearEntry();
    void backspaceClicked();

protected:
    void createUI();
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event) override;
    QPushButton *createButton(const QString &text, const QString &style = "");
    double calculate(double left, double right, const QString &op);
    void abortOperation();

private:
    QLineEdit *display;
    bool waitingForOperand;
    double pendingValue;
    QString pendingOperator;
    QStack<double> memory;
    QMap<QString, QPushButton*> buttonMap;

    const QString numberButtonStyle = 
        "QPushButton { "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3a3a3a, stop:1 #2d2d2d);"
        "border: none;"
        "border-radius: 8px;"
        "color: white;"
        "font-size: 18px;"
        "font-weight: bold;"
        "padding: 12px;"
        "}"
        "QPushButton:hover { "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4a4a4a, stop:1 #3d3d3d);"
        "}"
        "QPushButton:pressed { "
        "background-color: #1f1f1f;"
        "padding-left: 14px; padding-top: 14px;"
        "}";

    const QString operatorButtonStyle = 
        "QPushButton { "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffb347, stop:1 #ff9500);"
        "border: none;"
        "border-radius: 8px;"
        "color: white;"
        "font-size: 18px;"
        "font-weight: bold;"
        "padding: 12px;"
        "box-shadow: 0px 3px 6px rgba(0,0,0,0.3);"
        "}"
        "QPushButton:hover { "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffcc66, stop:1 #ffaa33);"
        "transform: scale(1.05);"
        "}"
        "QPushButton:pressed { "
        "background-color: #cc7700;"
        "padding-left: 14px; padding-top: 14px;"
        "}";

    const QString functionButtonStyle = 
        "QPushButton { "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b0b0b0, stop:1 #a5a5a5);"
        "border: none;"
        "border-radius: 8px;"
        "color: black;"
        "font-size: 16px;"
        "font-weight: bold;"
        "padding: 12px;"
        "box-shadow: 0px 2px 4px rgba(0,0,0,0.2);"
        "transition: all 0.2s ease;"
        "}"
        "QPushButton:hover { "
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0c0c0, stop:1 #b5b5b5);"
        "transform: scale(1.03);"
        "}"
        "QPushButton:pressed { "
        "background-color: #959595;"
        "padding-left: 14px; padding-top: 14px;"
        "}";
};

#endif // CALCULATOR_H