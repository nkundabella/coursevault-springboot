#include "MainWindow.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QRegularExpression>

CalcWindow::CalcWindow(QWidget* parent)
	: QWidget(parent), display(new QLineEdit(this)), currentOperator(QChar('\0')), newNumber(true) {
	QVBoxLayout* vbox = new QVBoxLayout(this);
	QGridLayout* grid = new QGridLayout();

	display->setReadOnly(true);
	display->setAlignment(Qt::AlignRight);
	display->setText("0");
	display->setMinimumHeight(40);
	vbox->addWidget(display);
	vbox->addLayout(grid);

	auto makeBtn = [&](const QString& text, int row, int col, QObject* recv, const char* slot) {
		QPushButton* btn = new QPushButton(text, this);
		btn->setMinimumSize(60, 40);
		grid->addWidget(btn, row, col);
		QObject::connect(btn, SIGNAL(clicked()), recv, slot);
		return btn;
	};

	// Row 1: Clear, divide
	makeBtn("C", 0, 0, this, SLOT(onClearClicked()));
	makeBtn("/", 0, 3, this, SLOT(onOperatorClicked()));

	// Digits
	int row = 1, col = 0;
	for (int d = 7; d <= 9; ++d) { makeBtn(QString::number(d), row, col++, this, SLOT(onDigitClicked())); }
	col = 0; row = 2; for (int d = 4; d <= 6; ++d) { makeBtn(QString::number(d), row, col++, this, SLOT(onDigitClicked())); }
	col = 0; row = 3; for (int d = 1; d <= 3; ++d) { makeBtn(QString::number(d), row, col++, this, SLOT(onDigitClicked())); }

	// Zero, dot, equals
	makeBtn("0", 4, 0, this, SLOT(onDigitClicked()));
	makeBtn(".", 4, 1, this, SLOT(onDotClicked()));
	makeBtn("=", 4, 2, this, SLOT(onEqualsClicked()));

	// Operators
	makeBtn("*", 1, 3, this, SLOT(onOperatorClicked()));
	makeBtn("-", 2, 3, this, SLOT(onOperatorClicked()));
	makeBtn("+", 3, 3, this, SLOT(onOperatorClicked()));

	setWindowTitle("Qt Calculator");
	resize(300, 300);
}

void CalcWindow::onDigitClicked() {
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;
	appendDigit(btn->text());
}

void CalcWindow::onDotClicked() {
	if (newNumber) {
		currentNumber = "0";
		newNumber = false;
	}
	if (!currentNumber.contains('.')) {
		currentNumber += ".";
		updateDisplay(currentNumber);
	}
}

void CalcWindow::onOperatorClicked() {
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;
	applyOperator(btn->text()[0]);
}

void CalcWindow::onEqualsClicked() { compute(); }

void CalcWindow::onClearClicked() {
	currentNumber = "0";
	previousNumber.clear();
	currentOperator = QChar('\0');
	newNumber = true;
	updateDisplay(currentNumber);
}

void CalcWindow::appendDigit(const QString& digitText) {
	if (newNumber) {
		currentNumber = digitText;
		newNumber = false;
	} else {
		if (currentNumber == "0") currentNumber = digitText; else currentNumber += digitText;
	}
	updateDisplay(currentNumber);
}

void CalcWindow::applyOperator(const QChar opChar) {
	if (!newNumber && !previousNumber.isEmpty() && currentOperator != QChar('\0')) {
		compute();
	}
	previousNumber = currentNumber;
	currentOperator = opChar;
	newNumber = true;
}

void CalcWindow::compute() {
	if (currentOperator == QChar('\0') || previousNumber.isEmpty()) return;
	bool okPrev = false, okCurr = false;
	double prev = previousNumber.toDouble(&okPrev);
	double curr = currentNumber.toDouble(&okCurr);
	if (!okPrev || !okCurr) return;

	double result = 0.0;
	if (currentOperator == '+') result = prev + curr;
	else if (currentOperator == '-') result = prev - curr;
	else if (currentOperator == '*') result = prev * curr;
	else if (currentOperator == '/') {
		if (curr == 0.0) { updateDisplay("Error"); return; }
		result = prev / curr;
	}

	QString resultText;
	if (qFuzzyCompare(result, static_cast<double>(static_cast<long long>(result)))) {
		resultText = QString::number(static_cast<long long>(result));
	} else {
		resultText = QString::number(result, 'g', 12);
	}
	currentNumber = resultText;
	previousNumber.clear();
	currentOperator = QChar('\0');
	newNumber = true;
	updateDisplay(currentNumber);
}

void CalcWindow::updateDisplay(const QString& text) {
	display->setText(text);
}


