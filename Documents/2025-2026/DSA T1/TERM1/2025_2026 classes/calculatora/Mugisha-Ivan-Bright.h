#ifndef MUGISHA-IVAN-BRIGHT_H
#define MUGISHA-IVAN-BRIGHT_H

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
    double firstNum;
    bool UserIsTypingSecondNum;
    bool result_logged = false;
private slots:
    void digit_pressed();
    void operation_pressed();
    void equals_pressed();

    void clear_pressed();
    void backspace_pressed();
    void square_pressed();
    void sqrt_pressed();
    void percent_pressed();


};
#endif // MUGISHA-IVAN-BRIGHT_H
