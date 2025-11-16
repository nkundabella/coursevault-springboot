#pragma once
#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

class Calculator {
public:
    double Evaluate(const std::string& expr);

private:
    int precedence(char op);
    double applyOp(double a, double b, char op);
};
