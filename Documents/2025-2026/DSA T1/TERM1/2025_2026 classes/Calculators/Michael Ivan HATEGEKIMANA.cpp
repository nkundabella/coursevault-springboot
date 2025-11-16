#include "Calculator.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>
using namespace std;

bool Calculator::is_operator_found(const std::string& expression, char operator_symbol) {
    return expression.find(operator_symbol) != std::string::npos;
}

big_float Calculator::process_operator(const std::string& expression, char operator_symbol, 
    big_float(*operation)(big_float, big_float)) {
    auto operator_pos = expression.find(operator_symbol);
    big_float left_operand = recursive_calculate(expression.substr(0, operator_pos));
    big_float right_operand = recursive_calculate(expression.substr(operator_pos + 1));
    return operation(left_operand, right_operand);
}

string Calculator::replace_binary_minus(const string& expression) {
    string processed_expresion = expression;
    size_t pos = 0;
    string minus = "-";
    string plus_minus = "+-";

    while ((pos = processed_expresion.find(minus, pos)) != string::npos) {
        if (pos > 0 && (isdigit(processed_expresion[pos - 1]) || processed_expresion[pos - 1] == '.')) {
            processed_expresion.replace(pos, minus.length(), plus_minus);
        }
        pos += plus_minus.length();
    }

    return processed_expresion;
}

big_float add_operation(big_float left, big_float right) {
    return left + right;
}

big_float multiply_operation(big_float left, big_float right) {
    return left * right;
}

big_float divide_operation(big_float left, big_float right) {
    return left / right;
}

big_float modulus_operation(big_float left, big_float right) {
    return fmod(left, right);
}

big_float Calculator::recursive_calculate(const std::string& expression) {
    if (is_operator_found(expression, '+')) {
        return process_operator(expression, '+', add_operation);
    }
    if (is_operator_found(expression, '*')) {
        return process_operator(expression, '*', multiply_operation);
    }
    if (is_operator_found(expression, '/')) {
        return process_operator(expression, '/', divide_operation);
    }
    if (is_operator_found(expression, '%')) {
        return process_operator(expression, '%', modulus_operation);
    }
    return expression.empty() ? 0.0L : big_float(expression);
}

bool Calculator::is_valid_expression(const std::string& expression) {
    for (char c : expression) {
        if (!isdigit(c) && c != '.' && c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != ' ') {
            return false;
        }
    }
    return true;
}

bool Calculator::has_valid_operator_placement(const std::string& expression) {
    if (expression.empty()) return false;
    
    for (size_t i = 0; i < expression.length() - 1; i++) {
        char current = expression[i];
        char next = expression[i + 1];
        
        if (current == ' ') continue;
        
        bool current_is_op = (current == '+' || current == '*' || current == '/' || current == '%');
        bool next_is_op = (next == '+' || next == '-' || next == '*' || next == '/' || next == '%');
        
        if (current_is_op && next_is_op && next != '-') {
            return false;
        }
    }
    
    char first = expression.front();
    char last = expression.back();
    
    if (first == '*' || first == '/' || first == '%' || first == '+') return false;
    if (last == '+' || last == '-' || last == '*' || last == '/' || last == '%') return false;
    
    return true;
}

std::string Calculator::sanitize_expression(const std::string& expression) {
    std::string sanitized;
    for (char c : expression) {
        if (isdigit(c) || c == '.' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            sanitized += c;
        }
    }
    return sanitized;
}

big_float Calculator::calculate(const std::string& expression) {
    if (expression.empty()) {
        throw std::invalid_argument("Empty expression");
    }
    
    std::string clean_expr = sanitize_expression(expression);
    
    if (clean_expr.empty()) {
        throw std::invalid_argument("No valid characters in expression");
    }
    
    if (!has_valid_operator_placement(clean_expr)) {
        throw std::invalid_argument("Invalid operator placement");
    }
    
    size_t div_pos = clean_expr.find('/');
    if (div_pos != std::string::npos) {
        std::string right_part = clean_expr.substr(div_pos + 1);
        try {
            big_float divisor = big_float(right_part);
            if (divisor == 0) {
                throw std::invalid_argument("Division by zero");
            }
        } catch (...) {
        }
    }
    
    size_t mod_pos = clean_expr.find('%');
    if (mod_pos != std::string::npos) {
        std::string right_part = clean_expr.substr(mod_pos + 1);
        try {
            big_float divisor = big_float(right_part);
            if (divisor == 0) {
                throw std::invalid_argument("Modulus by zero");
            }
        } catch (...) {
        }   
    }
    
    try {
        return recursive_calculate(replace_binary_minus(clean_expr));
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid mathematical expression");
    }
}