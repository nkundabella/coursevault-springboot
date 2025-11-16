#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFont>
#include <QSizePolicy>
#include <QString>
#include <QChar>
#include <cmath>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitPressed();
    void operatorPressed();
    void equalsPressed();
    void clearPressed();
    void backspacePressed();
    void decimalPressed();

private:
    void createWidgets();
    void createLayout();
    void connectSignals();
    void updateDisplay();
    double performCalculation(double first, double second, char op);
    bool isOperator(const QString &text);
    void resetCalculator();

    // UI Components
    QLineEdit *display;
    QPushButton *digitButtons[10];
    QPushButton *operatorButtons[5]; // +, -, *, /, %
    QPushButton *equalsButton;
    QPushButton *clearButton;
    QPushButton *backspaceButton;
    QPushButton *decimalButton;

    // Calculator state
    double firstOperand;
    double secondOperand;
    QString currentOperator;
    bool waitingForSecondOperand;
    bool operatorPressed;
    QString displayText;
};

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , firstOperand(0.0)
    , secondOperand(0.0)
    , waitingForSecondOperand(false)
    , operatorPressed(false)
    , displayText("0")
{
    setWindowTitle("Arithmetic Calculator");
    setMinimumSize(300, 400);
    setMaximumSize(400, 500);
    
    createWidgets();
    createLayout();
    connectSignals();
    updateDisplay();
}

Calculator::~Calculator()
{
}

void Calculator::createWidgets()
{
    // Create display
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    
    // Set display font
    QFont displayFont = display->font();
    displayFont.setPointSize(16);
    display->setFont(displayFont);
    
    // Create digit buttons (0-9)
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = new QPushButton(QString::number(i), this);
        digitButtons[i]->setMinimumSize(60, 60);
        digitButtons[i]->setFont(QFont("Arial", 12));
    }
    
    // Create operator buttons
    operatorButtons[0] = new QPushButton("+", this);  // Addition
    operatorButtons[1] = new QPushButton("-", this);  // Subtraction
    operatorButtons[2] = new QPushButton("*", this);  // Multiplication
    operatorButtons[3] = new QPushButton("/", this);  // Division
    operatorButtons[4] = new QPushButton("%", this);  // Modulus
    
    for (int i = 0; i < 5; ++i) {
        operatorButtons[i]->setMinimumSize(60, 60);
        operatorButtons[i]->setFont(QFont("Arial", 12));
        operatorButtons[i]->setStyleSheet("QPushButton { background-color: #ff9500; color: white; }");
    }
    
    // Create special buttons
    equalsButton = new QPushButton("=", this);
    equalsButton->setMinimumSize(60, 60);
    equalsButton->setFont(QFont("Arial", 12));
    equalsButton->setStyleSheet("QPushButton { background-color: #ff9500; color: white; }");
    
    clearButton = new QPushButton("C", this);
    clearButton->setMinimumSize(60, 60);
    clearButton->setFont(QFont("Arial", 12));
    clearButton->setStyleSheet("QPushButton { background-color: #a6a6a6; color: black; }");
    
    backspaceButton = new QPushButton("←", this);
    backspaceButton->setMinimumSize(60, 60);
    backspaceButton->setFont(QFont("Arial", 12));
    backspaceButton->setStyleSheet("QPushButton { background-color: #a6a6a6; color: black; }");
    
    decimalButton = new QPushButton(".", this);
    decimalButton->setMinimumSize(60, 60);
    decimalButton->setFont(QFont("Arial", 12));
}

void Calculator::createLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Add display
    mainLayout->addWidget(display);
    
    // Create button grid layout
    QGridLayout *buttonLayout = new QGridLayout();
    
    // Row 1: 7, 8, 9, /
    buttonLayout->addWidget(digitButtons[7], 0, 0);
    buttonLayout->addWidget(digitButtons[8], 0, 1);
    buttonLayout->addWidget(digitButtons[9], 0, 2);
    buttonLayout->addWidget(operatorButtons[3], 0, 3); // Division
    
    // Row 2: 4, 5, 6, *
    buttonLayout->addWidget(digitButtons[4], 1, 0);
    buttonLayout->addWidget(digitButtons[5], 1, 1);
    buttonLayout->addWidget(digitButtons[6], 1, 2);
    buttonLayout->addWidget(operatorButtons[2], 1, 3); // Multiplication
    
    // Row 3: 1, 2, 3, -
    buttonLayout->addWidget(digitButtons[1], 2, 0);
    buttonLayout->addWidget(digitButtons[2], 2, 1);
    buttonLayout->addWidget(digitButtons[3], 2, 2);
    buttonLayout->addWidget(operatorButtons[1], 2, 3); // Subtraction
    
    // Row 4: 0, ., =, +
    buttonLayout->addWidget(digitButtons[0], 3, 0);
    buttonLayout->addWidget(decimalButton, 3, 1);
    buttonLayout->addWidget(equalsButton, 3, 2);
    buttonLayout->addWidget(operatorButtons[0], 3, 3); // Addition
    
    // Row 5: C, ←, %
    buttonLayout->addWidget(clearButton, 4, 0);
    buttonLayout->addWidget(backspaceButton, 4, 1);
    buttonLayout->addWidget(operatorButtons[4], 4, 2); // Modulus
    
    mainLayout->addLayout(buttonLayout);
    
    // Set spacing
    buttonLayout->setSpacing(5);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);
}

void Calculator::connectSignals()
{
    // Connect digit buttons
    for (int i = 0; i < 10; ++i) {
        connect(digitButtons[i], &QPushButton::clicked, this, &Calculator::digitPressed);
    }
    
    // Connect operator buttons
    for (int i = 0; i < 5; ++i) {
        connect(operatorButtons[i], &QPushButton::clicked, this, &Calculator::operatorPressed);
    }
    
    // Connect special buttons
    connect(equalsButton, &QPushButton::clicked, this, &Calculator::equalsPressed);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearPressed);
    connect(backspaceButton, &QPushButton::clicked, this, &Calculator::backspacePressed);
    connect(decimalButton, &QPushButton::clicked, this, &Calculator::decimalPressed);
}

void Calculator::digitPressed()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString digitValue = clickedButton->text();
    
    if (waitingForSecondOperand) {
        displayText = digitValue;
        waitingForSecondOperand = false;
    } else {
        if (displayText == "0") {
            displayText = digitValue;
        } else {
            displayText += digitValue;
        }
    }
    
    operatorPressed = false;
    updateDisplay();
}

void Calculator::operatorPressed()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString operatorValue = clickedButton->text();
    
    if (!operatorPressed && !waitingForSecondOperand) {
        firstOperand = displayText.toDouble();
        currentOperator = operatorValue;
        waitingForSecondOperand = true;
        operatorPressed = true;
    } else if (operatorPressed) {
        // Replace the current operator
        currentOperator = operatorValue;
    }
}

void Calculator::equalsPressed()
{
    if (!waitingForSecondOperand && !currentOperator.isEmpty()) {
        secondOperand = displayText.toDouble();
        
        // Check for division by zero
        if (currentOperator == "/" && secondOperand == 0.0) {
            QMessageBox::warning(this, "Error", "Cannot divide by zero!");
            return;
        }
        
        // Check for modulus by zero
        if (currentOperator == "%" && secondOperand == 0.0) {
            QMessageBox::warning(this, "Error", "Cannot perform modulus by zero!");
            return;
        }
        
        double result = performCalculation(firstOperand, secondOperand, currentOperator[0].toLatin1());
        
        // Check for overflow
        if (std::isinf(result) || std::isnan(result)) {
            QMessageBox::warning(this, "Error", "Result is too large or invalid!");
            return;
        }
        
        // Format result with up to 2 decimal places
        displayText = QString::number(result, 'f', 2);
        
        // Remove trailing zeros and decimal point if not needed
        if (displayText.contains('.')) {
            displayText = displayText.remove(QRegExp("0+$"));
            displayText = displayText.remove(QRegExp("\\.$"));
        }
        
        updateDisplay();
        
        // Reset state for next calculation
        firstOperand = result;
        currentOperator.clear();
        waitingForSecondOperand = true;
        operatorPressed = false;
    }
}

void Calculator::clearPressed()
{
    resetCalculator();
}

void Calculator::backspacePressed()
{
    if (!waitingForSecondOperand && displayText.length() > 1) {
        displayText.chop(1);
    } else if (!waitingForSecondOperand && displayText.length() == 1) {
        displayText = "0";
    }
    updateDisplay();
}

void Calculator::decimalPressed()
{
    if (waitingForSecondOperand) {
        displayText = "0.";
        waitingForSecondOperand = false;
    } else if (!displayText.contains('.')) {
        displayText += ".";
    }
    updateDisplay();
}

void Calculator::updateDisplay()
{
    display->setText(displayText);
}

double Calculator::performCalculation(double first, double second, char op)
{
    switch (op) {
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '*':
            return first * second;
        case '/':
            return first / second;
        case '%':
            return std::fmod(first, second);
        default:
            return 0.0;
    }
}

bool Calculator::isOperator(const QString &text)
{
    return text == "+" || text == "-" || text == "*" || text == "/" || text == "%";
}

void Calculator::resetCalculator()
{
    firstOperand = 0.0;
    secondOperand = 0.0;
    currentOperator.clear();
    waitingForSecondOperand = false;
    operatorPressed = false;
    displayText = "0";
    updateDisplay();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    Calculator calculator;
    calculator.show();
    
    return app.exec();
}

#include "calculator.moc"
