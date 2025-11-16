#include "mainwindow.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsColorizeEffect>
#include <QEasingCurve>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      pendingOperand(0.0),
      pendingOperator(QString()),
      waitingForOperand(true),
      currentInput("")
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(12,12,12,12);
    mainLayout->setSpacing(8);

    historyLabel = new QLabel("");
    historyLabel->setAlignment(Qt::AlignRight);
    historyLabel->setStyleSheet("color: gray; font-size: 16px;");
    mainLayout->addWidget(historyLabel);

    display = new QLineEdit("0");
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);
    display->setMaxLength(32);
    display->setStyleSheet(
        "QLineEdit { font-size: 32px; padding: 14px; "
        "border: none; background: #1C1C1C; color: white; border-radius: 10px; }"
    );
    mainLayout->addWidget(display);

    QGridLayout *grid = new QGridLayout;
    grid->setSpacing(10);

    // Row 1
    grid->addWidget(createButton("AC", SLOT(onClearClicked()), "#A5A5A5"), 0,0);
    grid->addWidget(createButton("±", SLOT(onToggleSignClicked()), "#A5A5A5"), 0,1);
    grid->addWidget(createButton("%", SLOT(onPercentClicked()), "#A5A5A5"), 0,2);
    grid->addWidget(createButton("÷", SLOT(onOperatorClicked()), "#FF9500", true), 0,3);

    // Row 2
    grid->addWidget(createButton("7", SLOT(onDigitClicked())), 1,0);
    grid->addWidget(createButton("8", SLOT(onDigitClicked())), 1,1);
    grid->addWidget(createButton("9", SLOT(onDigitClicked())), 1,2);
    grid->addWidget(createButton("×", SLOT(onOperatorClicked()), "#FF9500", true), 1,3);

    // Row 3
    grid->addWidget(createButton("4", SLOT(onDigitClicked())), 2,0);
    grid->addWidget(createButton("5", SLOT(onDigitClicked())), 2,1);
    grid->addWidget(createButton("6", SLOT(onDigitClicked())), 2,2);
    grid->addWidget(createButton("−", SLOT(onOperatorClicked()), "#FF9500", true), 2,3);

    // Row 4
    grid->addWidget(createButton("1", SLOT(onDigitClicked())), 3,0);
    grid->addWidget(createButton("2", SLOT(onDigitClicked())), 3,1);
    grid->addWidget(createButton("3", SLOT(onDigitClicked())), 3,2);
    grid->addWidget(createButton("+", SLOT(onOperatorClicked()), "#FF9500", true), 3,3);

    // Row 5
    QPushButton *zeroButton = createButton("0", SLOT(onDigitClicked()));
    grid->addWidget(zeroButton, 4,0,1,2);
    grid->addWidget(createButton(".", SLOT(onDigitClicked())), 4,2);
    grid->addWidget(createButton("=", SLOT(onEqualsClicked()), "#FF9500", true), 4,3);

    mainLayout->addLayout(grid);

    setStyleSheet("background-color: #000000;");
    setWindowTitle("Calculator");
    setFixedSize(360,520);
}

// ==================== Button helpers ====================

QPushButton* MainWindow::createButton(const QString &text, const char* slot,
                                      const QString &color, bool isOperator)
{
    Q_UNUSED(isOperator)

    QPushButton *button = new QPushButton(text);
    button->setMinimumSize(72,72);
    button->setCursor(Qt::PointingHandCursor);

    QString style =
        "QPushButton { font-size:20px; border:none; border-radius:36px; "
        "background:" + color + "; color:white; }"
        "QPushButton:hover { transform: translateY(-1px); }";
    button->setStyleSheet(style);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(button);
    shadow->setBlurRadius(18);
    shadow->setOffset(2,3);
    shadow->setColor(QColor(0,0,0,160));
    button->setGraphicsEffect(shadow);

    connect(button, SIGNAL(clicked()), this, slot);

    connect(button, &QPushButton::pressed, [button]() {
        QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(button);
        effect->setColor(Qt::white);
        effect->setStrength(0.0);
        button->setGraphicsEffect(effect);

        QPropertyAnimation *flash = new QPropertyAnimation(effect, "strength");
        flash->setDuration(160);
        flash->setStartValue(0.0);
        flash->setKeyValueAt(0.5, 0.45);
        flash->setEndValue(0.0);
        flash->setEasingCurve(QEasingCurve::OutQuad);
        flash->start(QAbstractAnimation::DeleteWhenStopped);
    });

    return button;
}

// ==================== Slots ====================

void MainWindow::appendDigit(const QString &digit) {
    if (digit == "." && currentInput.contains('.')) return;

    if (waitingForOperand) {
        currentInput = (digit == ".") ? "0." : digit;
        waitingForOperand = false;
    } else {
        currentInput += digit;
    }
    display->setText(currentInput);
    historyLabel->setText(pendingOperator.isEmpty() ? currentInput
                                                   : QString::number(pendingOperand) + " " + pendingOperator + " " + currentInput);
}

void MainWindow::appendOperator(const QString &op) {
    double value = currentInput.toDouble();

    if (!pendingOperator.isEmpty()) {
        if (!calculate(value)) {
            onClearClicked();
            display->setText("Error");
            return;
        }
    } else {
        pendingOperand = value;
    }

    pendingOperator = op;
    waitingForOperand = true;
    currentInput.clear();
    historyLabel->setText(QString::number(pendingOperand) + " " + pendingOperator);
}

void MainWindow::onDigitClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    appendDigit(button->text());
}

void MainWindow::onOperatorClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();
    if (op == "×") op = "*";
    else if (op == "÷") op = "/";
    else if (op == "−") op = "-";
    appendOperator(op);
}

void MainWindow::onEqualsClicked() {
    double value = currentInput.toDouble();

    if (pendingOperator.isEmpty()) return;

    if (!calculate(value)) {
        onClearClicked();
        display->setText("Error");
        return;
    }

    display->setText(QString::number(pendingOperand, 'g', 12));
    historyLabel->setText("");
    pendingOperator.clear();
    waitingForOperand = true;
    currentInput.clear();
}

void MainWindow::onClearClicked() {
    display->setText("0");
    historyLabel->setText("");
    pendingOperand = 0.0;
    pendingOperator.clear();
    currentInput.clear();
    waitingForOperand = true;
}

void MainWindow::onPercentClicked() {
    double value = currentInput.toDouble() * 0.01;
    currentInput = QString::number(value, 'g', 12);
    display->setText(currentInput);
    waitingForOperand = true;
}

void MainWindow::onToggleSignClicked() {
    double value = currentInput.toDouble();
    value = -value;
    currentInput = QString::number(value, 'g', 12);
    display->setText(currentInput);
}

// ==================== Calculation ====================

bool MainWindow::calculate(double rightOperand) {
    if (pendingOperator == "+") pendingOperand += rightOperand;
    else if (pendingOperator == "-") pendingOperand -= rightOperand;
    else if (pendingOperator == "*") pendingOperand *= rightOperand;
    else if (pendingOperator == "/") {
        if (rightOperand == 0.0) return false;
        pendingOperand /= rightOperand;
    } else return false;

    return true;
}

// ==================== Keyboard support ====================

#include <QKeyEvent>
void MainWindow::keyPressEvent(QKeyEvent *event) {
    QString keyText = event->text();

    if (keyText >= "0" && keyText <= "9") appendDigit(keyText);
    else if (keyText == ".") appendDigit(".");
    else if (keyText == "+" || keyText == "-" || keyText == "*" || keyText == "/") appendOperator(keyText);
    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) onEqualsClicked();
    else if (event->key() == Qt::Key_Backspace) {
        if (!currentInput.isEmpty()) {
            currentInput.chop(1);
            display->setText(currentInput.isEmpty() ? "0" : currentInput);
        }
    }
    else if (event->key() == Qt::Key_Escape) onClearClicked();
}