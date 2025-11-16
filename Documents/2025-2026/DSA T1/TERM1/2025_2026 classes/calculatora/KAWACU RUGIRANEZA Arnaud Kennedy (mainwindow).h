#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLineEdit *display;
    QLabel *historyLabel;

    QString pendingOperator;
    double pendingOperand;
    bool waitingForOperand;
    QString currentInput; // track input for decimals and chaining

    QPushButton* createButton(const QString &text, const char* slot,
                              const QString &color = "#333333", bool isOperator = false);

    void appendDigit(const QString &digit);
    void appendOperator(const QString &op);
    bool calculate(double rightOperand);

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onPercentClicked();
    void onToggleSignClicked();
};

#endif // MAINWINDOW_H