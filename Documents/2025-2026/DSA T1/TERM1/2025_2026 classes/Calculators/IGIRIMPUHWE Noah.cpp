#include <gtkmm.h>
#include <string>
#include <stdexcept>
#include <cctype>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <sstream>
#include <algorithm>

class Calculator : public Gtk::Window {
public:
    Calculator() {
        set_title("Enhanced Calculator");
        set_default_size(400, 500);  // Increased size for more buttons
        set_resizable(true);         // Allow resizing

        // Main layout
        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
        vbox->set_margin(10);
        set_child(*vbox);

        // Input area
        auto hbox_input = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
        auto input_label = Gtk::make_managed<Gtk::Label>("Expression:");
        input_label->set_margin_end(5);

        input_field.set_width_chars(30);
        input_field.set_placeholder_text("Enter expression or click buttons");
        input_field.set_text("0");
        input_field.set_editable(true); // User can type input
        input_field.set_margin_end(10);

        hbox_input->append(*input_label);
        hbox_input->append(input_field);
        vbox->append(*hbox_input);

        // Result label
        result_label.set_text("Result: 0");
        result_label.set_margin_top(10);
        result_label.get_style_context()->add_class("title-4");
        vbox->append(result_label);

        // Button Grid
        auto grid = Gtk::make_managed<Gtk::Grid>();
        grid->set_row_spacing(5);
        grid->set_column_spacing(5);
        grid->set_margin_top(10);

        // Updated button layout for more functionality
        std::vector<std::vector<std::string>> layout = {
            {"(", ")", "%", "/"},
            {"7", "8", "9", "*"},
            {"4", "5", "6", "-"},
            {"1", "2", "3", "+"},
            {"0", ".", "+/-", "="},
            {"Back", "Clear"}
        };

        for (size_t row = 0; row < layout.size(); ++row) {
            for (size_t col = 0; col < layout[row].size(); ++col) {
                const std::string& label = layout[row][col];
                auto button = Gtk::make_managed<Gtk::Button>(label);
                button->set_margin(5);

                if (label == "=") {
                    button->get_style_context()->add_class("suggested-action");
                    button->signal_clicked().connect([this]() { calculate_result(); });
                    grid->attach(*button, col, row, 1, 1); // Standard size
                } else if (label == "Clear") {
                    button->get_style_context()->add_class("destructive-action");
                    button->signal_clicked().connect([this]() { clear_fields(); });
                    grid->attach(*button, 1, row, 2, 1); // Span 2 columns
                } else if (label == "Back") {
                    button->get_style_context()->add_class("destructive-action");
                    button->signal_clicked().connect([this]() { backspace(); });
                    grid->attach(*button, 0, row, 1, 1);
                } else if (label == "+/-") {
                    button->get_style_context()->add_class("suggested-action");
                    button->signal_clicked().connect([this]() { toggle_sign(); });
                } else if (label == "%" || label == "+" || label == "-" || label == "*" || label == "/") {
                    button->get_style_context()->add_class("suggested-action");
                    button->signal_clicked().connect([this, label]() { append_operation(label[0]); });
                } else if (label == "(" || label == ")") {
                    button->get_style_context()->add_class("suggested-action");
                    button->signal_clicked().connect([this, label]() { append_parenthesis(label[0]); });
                } else if (label == ".") {
                    button->get_style_context()->add_class("suggested-action");
                    button->signal_clicked().connect([this]() { append_decimal(); });
                } else {
                    button->get_style_context()->add_class("number-button");
                    button->signal_clicked().connect([this, label]() { append_number(std::stoi(label)); });
                }

                if (label != "=" && label != "Clear" && label != "Back") {
                    grid->attach(*button, col, row);
                }
            }
        }

        vbox->append(*grid);

        // Keyboard enter = calculate
        input_field.signal_activate().connect([this]() { calculate_result(); });

        // CSS Styling (updated for better visuals)
        auto css = Gtk::CssProvider::create();
        css->load_from_data(R"(
            button {
                min-width: 60px;
                min-height: 45px;
                background-color: #f0f0f0;
                border-radius: 5px;
                font-size: 16px;
            }
            .suggested-action {
                background-color: #4CAF50;
                color: white;
            }
            .destructive-action {
                background-color: #f44336;
                color: white;
            }
            .number-button {
                background-color: #e0e0e0;
            }
            entry {
                border: 1px solid #ccc;
                border-radius: 3px;
                padding: 8px;
                font-size: 18px;
            }
            .title-4 {
                font-weight: bold;
                font-size: 20px;
            }
        )");
        get_style_context()->add_provider(css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

private:
    Gtk::Entry input_field;
    Gtk::Label result_label;

    void append_number(int num) {
        std::string current = input_field.get_text();
        if (current == "0") current.clear();
        current += std::to_string(num);
        input_field.set_text(current);
        input_field.set_position(-1); // Move cursor to end
    }

    void append_operation(char op) {
        std::string current = input_field.get_text();
        if (current.empty()) return;

        const std::string ops = "+-*/%";
        char last = current.back();

        if (ops.find(last) != std::string::npos || last == '(') {
            // Allow unary after operator or (
            if (op == '-') {
                current += op;
            } else if (ops.find(op) != std::string::npos) {
                current.back() = op; // Replace last operator
            }
        } else {
            current += op;
        }

        input_field.set_text(current);
        input_field.set_position(-1);
    }

    void append_parenthesis(char paren) {
        std::string current = input_field.get_text();
        current += paren;
        input_field.set_text(current);
        input_field.set_position(-1);
    }

    void append_decimal() {
        std::string current = input_field.get_text();
        if (current.empty()) {
            current = "0.";
        } else {
            // Check if last number already has decimal
            size_t last_op = current.find_last_of("+-*/%()");
            std::string last_num = current.substr(last_op == std::string::npos ? 0 : last_op + 1);
            if (last_num.find('.') == std::string::npos) {
                current += ".";
            }
        }
        input_field.set_text(current);
        input_field.set_position(-1);
    }

    void toggle_sign() {
        std::string current = input_field.get_text();
        if (current.empty() || current == "0") return;

        // Find the start of the last number
        size_t pos = current.size() - 1;
        while (pos > 0 && (std::isdigit(current[pos]) || current[pos] == '.')) --pos;
        if (pos > 0 && current[pos] == '-') {
            // Remove the minus
            current.erase(pos, 1);
        } else if (std::isdigit(current[pos]) || current[pos] == '.') {
            // Insert minus before the number
            current.insert(pos, "-");
        } else {
            // If after operator, add unary minus
            current += "-";
        }

        input_field.set_text(current);
        input_field.set_position(-1);
    }

    void backspace() {
        std::string current = input_field.get_text();
        if (!current.empty() && current != "0") {
            current.pop_back();
            if (current.empty()) current = "0";
            input_field.set_text(current);
            input_field.set_position(-1);
        }
    }

    void calculate_result() {
        std::string expression = input_field.get_text();

        try {
            // Check for empty or whitespace-only input
            std::string trimmed = expression;
            trimmed.erase(std::remove_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) { return std::isspace(ch); }), trimmed.end());
            if (trimmed.empty()) {
                throw std::runtime_error("Invalid expression: Empty input.");
            }

            double result = evaluate_expression(expression);
            std::string result_str = std::to_string(result);

            // Trim trailing .0
            if (result_str.find('.') != std::string::npos) {
                result_str.erase(result_str.find_last_not_of('0') + 1);
                if (result_str.back() == '.') result_str.pop_back();
            }

            input_field.set_text(result_str);
            result_label.set_text("Result: " + result_str);
        } catch (const std::exception& ex) {
            std::string err_msg = ex.what();
            show_error_dialog(err_msg);
            result_label.set_text("Result: " + err_msg);
            // Do not reset input_field; keep the original expression to show what caused the error
        }
    }

    void clear_fields() {
        input_field.set_text("0");
        result_label.set_text("Result: 0");
    }

    void show_error_dialog(const std::string& message) {
        Gtk::MessageDialog dialog(*this, "Error", false, Gtk::MessageType::ERROR, Gtk::ButtonsType::OK);
        dialog.set_secondary_text(message);
        dialog.set_modal(true);
        dialog.signal_response().connect([&dialog](int) { dialog.hide(); });
        dialog.show();
    }

    // Expression evaluator using Shunting-Yard algorithm
    double evaluate_expression(const std::string& expr) {
        std::vector<std::string> tokens = tokenize(expr);
        std::vector<std::string> rpn = to_rpn(tokens);
        return evaluate_rpn(rpn);
    }

    std::vector<std::string> tokenize(const std::string& expr) {
        std::vector<std::string> tokens;
        std::string num;
        for (size_t i = 0; i < expr.length(); ++i) {
            char c = expr[i];
            if (std::isspace(static_cast<unsigned char>(c))) continue;
            if (std::isdigit(static_cast<unsigned char>(c)) || c == '.' || (c == '-' && (num.empty() && (i == 0 || !std::isdigit(static_cast<unsigned char>(expr[i-1])))))) {
                num += c;
            } else {
                if (!num.empty()) {
                    tokens.push_back(num);
                    num.clear();
                }
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')') {
                    tokens.push_back(std::string(1, c));
                } else {
                    throw std::runtime_error("Invalid character: " + std::string(1, c));
                }
            }
        }
        if (!num.empty()) tokens.push_back(num);
        return tokens;
    }

    int precedence(const std::string& op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/" || op == "%") return 2;
        return 0;
    }

    std::vector<std::string> to_rpn(const std::vector<std::string>& tokens) {
        std::vector<std::string> rpn;
        std::stack<std::string> ops;
        for (const auto& token : tokens) {
            if (is_number(token)) {
                rpn.push_back(token);
            } else if (token == "(") {
                ops.push(token);
            } else if (token == ")") {
                while (!ops.empty() && ops.top() != "(") {
                    rpn.push_back(ops.top());
                    ops.pop();
                }
                if (ops.empty()) throw std::runtime_error("Mismatched parentheses.");
                ops.pop();
            } else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                    rpn.push_back(ops.top());
                    ops.pop();
                }
                ops.push(token);
            }
        }
        while (!ops.empty()) {
            if (ops.top() == "(") throw std::runtime_error("Mismatched parentheses.");
            rpn.push_back(ops.top());
            ops.pop();
        }
        return rpn;
    }

    double evaluate_rpn(const std::vector<std::string>& rpn) {
        std::stack<double> stack;
        for (const auto& token : rpn) {
            if (is_number(token)) {
                stack.push(std::stod(token));
            } else {
                if (stack.size() < 2) throw std::runtime_error("Invalid expression.");
                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();
                if (token == "+") stack.push(a + b);
                else if (token == "-") stack.push(a - b);
                else if (token == "*") stack.push(a * b);
                else if (token == "/") {
                    if (b == 0.0) throw std::runtime_error("Error: Division by zero.");
                    stack.push(a / b);
                } else if (token == "%") {
                    if (b == 0.0) throw std::runtime_error("Error: Modulo by zero.");
                    stack.push(std::fmod(a, b));
                }
            }
        }
        if (stack.size() != 1) throw std::runtime_error("Invalid expression.");
        return stack.top();
    }

    bool is_number(const std::string& str) {
        if (str.empty()) return false;
        size_t start = (str[0] == '-') ? 1 : 0;
        bool dot_found = false;
        for (size_t i = start; i < str.size(); ++i) {
            if (str[i] == '.') {
                if (dot_found) return false;
                dot_found = true;
            } else if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create("org.example.advancedcalculator");
    return app->make_window_and_run<Calculator>(argc, argv);
}