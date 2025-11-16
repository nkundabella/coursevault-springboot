#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QRegularExpression>
#include <QGridLayout>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QSizePolicy>

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>


std::vector<std::string> tokenize(const std::string &expr)
{
    std::vector<std::string> tokens;
    std::istringstream iss(expr);

    std::string token;
    while (iss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

double evaluateExpression(const std::string &expr)
{
    auto tokens = tokenize(expr);
    if (tokens.empty()) throw std::runtime_error("Empty expression");

    double result = std::stod(tokens[0]);

    for (size_t i = 1; i + 1 < tokens.size(); i += 2)
    {
        std::string op = tokens[i];
        double val = std::stod(tokens[i + 1]);

        if (op == "+") result += val;
        else if (op == "-") result -= val;
        else if (op == "*") result *= val;
        else if (op == "/")
        {
            if (val == 0) throw std::runtime_error("Math error: division by zero");
            result /= val;
        }
        else throw std::runtime_error("Unknown operator: " + op);
    }

    return result;
}

bool isValidInput(const QString &input)
{
    for (QChar ch : input)
    {
        if (!ch.isDigit() && !QString("+-*/. ").contains(ch))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("DSA Calculator");

    QGridLayout *layout = new QGridLayout(&window);

    QLineEdit *inputDisplay = new QLineEdit();
    inputDisplay->setMinimumHeight(100);
    inputDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    inputDisplay->setAlignment(Qt::AlignLeft);
    QRegularExpression rx("[0-9+\\-*/. ]*");
    QValidator *validator = new QRegularExpressionValidator(rx, inputDisplay);
    inputDisplay->setValidator(validator);

    layout->addWidget(inputDisplay, 0, 0, 1, 4);


    QLineEdit *answerDisplay = new QLineEdit();
    answerDisplay->setMinimumHeight(60);
    answerDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    answerDisplay->setAlignment(Qt::AlignRight);
    answerDisplay->setReadOnly(true);

    layout->addWidget(answerDisplay, 1, 0, 1, 4);

    const QString buttons[5][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "x"},
        {"1", "2", "3", "-"},
        {"0", ".", "x²", "+"},
        {"(", ")", "=", "C"}
    };

    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            QPushButton *btn = new QPushButton(buttons[row][col]);
            btn->setMinimumSize(60, 40);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            QString btnText = buttons[row][col];

            if (btnText == "C")
                btn->setStyleSheet("background-color: red; color: white; font-weight: bold;");
            else if (btnText == "=")
                btn->setStyleSheet("background-color: white; color: black; font-weight: bold;");
            else if (QString("+-*/x").contains(btnText))
                btn->setStyleSheet("background-color: orange; color: white; font-size: 20px;");

            layout->addWidget(btn, row + 2, col);

            QObject::connect(btn, &QPushButton::clicked, [inputDisplay, answerDisplay, btn, &window]() {
                QString text = btn->text();
                QString current = inputDisplay->text();

                if (text == "x") text = "*";

                if (text == "C")
                {
                    inputDisplay->clear();
                    answerDisplay->clear();
                }
                else if (text == "=")
                {
                    try
                    {
                        QString inputText = inputDisplay->text();
                        if (!isValidInput(inputText))
                            throw std::runtime_error("Invalid input.");

                        std::string expr = inputText.toStdString();
                        double result = evaluateExpression(expr);
                        answerDisplay->setText(QString::number(result));
                    }
                    catch (const std::exception &e)
                    {
                        QMessageBox::warning(&window, "Error", e.what());
                    }
                }
                else if (text == "x²")
                {
                    QString currentText = inputDisplay->text().trimmed();
                    QRegularExpression re(R"((\d+(\.\d+)?)$)");
                    QRegularExpressionMatch match = re.match(currentText);

                    if (match.hasMatch())
                    {
                        QString numberStr = match.captured(1);

                        double number = numberStr.toDouble();

                        double squared = number * number;

                        currentText.chop(numberStr.length());
                        currentText += QString::number(squared);

                        inputDisplay->setText(currentText);
                    }
                }
                else
                {
                    if (QString("+-*/").contains(text))
                    {
                        if (!current.isEmpty() &&

                            !current.endsWith(' ') &&
                            !QString("+-*/").contains(current.right(1)))
                        {
                            current += " ";

                        }
                        current += text + " ";
                    }
                    else
                    {
                        current += text;
                    }

                    inputDisplay->setText(current);
                }
            });
        }
    }

    window.show();

    return app.exec();
}
