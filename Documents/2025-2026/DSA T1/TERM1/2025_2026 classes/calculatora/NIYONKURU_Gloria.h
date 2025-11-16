#ifndef NIYONKURU_GLORIA_H
#define NIYONKURU_GLORIA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digit_pressed();
    void dot_pressed();
    void math_operator_pressed();
    void equals_pressed();
    void clear_pressed();
    void delete_pressed();

private:
    Ui::MainWindow *ui;
};

#endif
