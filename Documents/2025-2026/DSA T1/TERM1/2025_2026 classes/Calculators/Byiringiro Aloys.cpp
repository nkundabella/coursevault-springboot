#include "calculator.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QString>
#include <QStack>
#include <QChar>
#include <cmath>
#include <QRegularExpressionValidator>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Calculator By ALOYS");

    display = new QLineEdit(this);
    display->setReadOnly(false);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);
    display->setPlaceholderText("0");

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[0-9+\\-*/.()]*"), this);
    display->setValidator(validator);

    grid = new QGridLayout;
    grid->setSpacing(6);

    QString buttons[5][4] = {
        {"CE", "C", "(", ")"},
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"}
    };

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 4; ++c) {
            addButton(buttons[r][c], r, c);
        }
    }

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(display);
    mainLay->addLayout(grid);
}

void Calculator::addButton(const QString &text, int row, int col, int rowSpan, int colSpan)
{
    QPushButton *btn = new QPushButton(text);
    grid->addWidget(btn, row, col, rowSpan, colSpan);
    connect(btn, &QPushButton::clicked, this, &Calculator::onButtonClicked);

    if (text == "CE") {
        btn->setObjectName("clearButton");
    } else if (text == "C") {
        btn->setObjectName("backspaceButton");
    }
}
static int precedence(QChar op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

static bool isOperator(QChar c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

static QList<QString> toRPN(const QString &s, bool &ok) {
    ok = true;
    QList<QString> output;
    QStack<QChar> ops;

    int i = 0;
    while (i < s.size()) {
        if (s[i].isSpace()) { ++i; continue; }
        if (s[i].isDigit() || s[i] == '.') {
            int j = i;
            while (j < s.size() && (s[j].isDigit() || s[j] == '.')) ++j;
            output.append(s.mid(i, j - i));
            i = j;
            continue;
        }

        QChar c = s[i];
        if (c == '(') {
            ops.push(c);
            ++i;
            continue;
        }
        if (c == ')') {
            bool found = false;
            while (!ops.isEmpty()) {
                QChar t = ops.pop();
                if (t == '(') { found = true; break; }
                output.append(QString(t));
            }
            if (!found) { ok = false; return {};}
            ++i; continue;
        }

        if (isOperator(c)) {
            bool unary = false;
            if (c == '-' || c == '+') {
                int k = i - 1;
                while (k >= 0 && s[k].isSpace()) --k;
                if (k < 0 || s[k] == '(' || isOperator(s[k])) unary = true;
            }

            if (unary) {
                int j = i + 1;
                bool seen_digit = false;
                if (j < s.size() && (s[j].isDigit() || s[j]=='.')) {
                    while (j < s.size() && (s[j].isDigit() || s[j]=='.')) ++j;
                    QString num = s.mid(i, j - i);
                    output.append(num);
                    i = j;
                    continue;
                } else {
                    ok = false; return {};
                }
            }
            while (!ops.isEmpty() && isOperator(ops.top()) && precedence(ops.top()) >= precedence(c)) {
                output.append(QString(ops.pop()));
            }
            ops.push(c);
            ++i; continue;
        }
        ok = false; return {};
    }

    while (!ops.isEmpty()) {
        QChar t = ops.pop();
        if (t == '(' || t == ')') { ok = false; return {}; }
        output.append(QString(t));
    }
    return output;
}

static double applyOp(double a, double b, QChar op, bool &ok) {
    ok = true;
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0.0) { ok = false; return 0; }
        return a / b;
    }
    ok = false; return 0;
}

static double evalRPN(const QList<QString> &rpn, bool &ok) {
    QStack<double> st;
    for (const QString &tok : rpn) {
        if (tok.isEmpty()) continue;
        if (tok.size() == 1 && isOperator(tok[0])) {
            if (st.size() < 2) { ok = false; return 0; }
            double b = st.pop(); double a = st.pop();
            bool innerOk;
            double res = applyOp(a, b, tok[0], innerOk);
            if (!innerOk) { ok = false; return 0; }
            st.push(res);
        } else {
            bool convOk = false;
            double v = tok.toDouble(&convOk);
            if (!convOk) { ok = false; return 0; }
            st.push(v);
        }
    }
    if (st.size() != 1) { ok = false; return 0; }
    return st.top();
}

double Calculator::evaluateExpression(const QString &expr, bool &ok)
{
    QString s = expr.trimmed();
    if (s.isEmpty()) { ok = false; return 0; }
    QList<QString> rpn = toRPN(s, ok);
    if (!ok) return 0;
    double res = evalRPN(rpn, ok);
    return res;
}

void Calculator::onButtonClicked()
{
    QPushButton *b = qobject_cast<QPushButton*>(sender());
    if (!b) return;
    QString t = b->text();

    if (t == "CE") {
        display->clear();
        return;
    }
    if (t == "C") {
        QString d = display->text();
        if (!d.isEmpty()) d.chop(1);
        display->setText(d);
        return;
    }
    if (t == "=") {
        QString expr = display->text();
        bool ok;
        double v = evaluateExpression(expr, ok);
        if (!ok) {
            display->setText("Mathematical Error");
        } else {
            QString out = QString::number(v, 'g', 12);
            display->setText(out);
        }
        return;
    }
    QString d = display->text();
    if (d == "Mathematical Error") d.clear();
    d.append(t);
    display->setText(d);
}