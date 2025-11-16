#ifndef UMURERWABONNETTE_H
#define UMURERWABONNETTE_H

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();
   void on_pushButton__released();
    void unary_operation_pressed();
    void on_pushButton_clear_released();
    void on_pushButton_equal_released();
    void binary_operation_pressed();
};

#endif // UMURERWABONNETTE_H
