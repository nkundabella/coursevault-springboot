#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    double firstNum;
    bool userIsTypingSecondNumber;


private slots:
    void digit_pressed();

    void on_pushButton_percentage_released();
    void on_pushButton_dot_released();
    void on_pushButton_plusnminus_released();
    void on_pushButton_delete_released();
    void on_pushButton_equal_released();
    void binary_operation_pressed();
    void on_pushButton_root_released();
    void on_pushButton_powernegative_released();
    void on_pushButton_tan_released();
    void on_pushButton_power2_released();
    void on_pushButton_high_released();
    void on_pushButton_in_released();
    void on_pushButton_sin_released();
    void on_pushButton_cos_released();
    void on_pushButton_closeb_released();
    void on_pushButton_bracket_released();
    void on_pushButton_exp_released();
    void on_pushButton_bslashc_released();
    void on_pushButton_rcl_released();
    void on_pushButton_store_released();

protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif
