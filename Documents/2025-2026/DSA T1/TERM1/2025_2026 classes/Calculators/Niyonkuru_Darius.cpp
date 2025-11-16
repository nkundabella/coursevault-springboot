#include <gtkmm.h>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

class CalculatorWindow : public Gtk::Window {
public:
    CalculatorWindow() {
        set_title("Modern Calculator");
        set_default_size(380, 520);
        set_border_width(20);
        set_resizable(false);

        // Enable keyboard events
        set_can_focus(true);
        add_events(Gdk::KEY_PRESS_MASK);
        signal_key_press_event().connect(sigc::mem_fun(*this, &CalculatorWindow::on_key_press));

        // Main vertical box with better spacing
        Gtk::Box* main_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 15));
        add(*main_box);

        // Display container with shadow effect
        Gtk::Frame* display_frame = Gtk::manage(new Gtk::Frame());
        display_frame->set_shadow_type(Gtk::SHADOW_IN);

        m_display = Gtk::manage(new Gtk::Entry());
        m_display->set_text("0");
        m_display->set_alignment(1.0);  // Right-align
        m_display->set_editable(false);
        m_display->set_can_focus(false);
        m_display->set_size_request(-1, 80);

        display_frame->add(*m_display);
        main_box->pack_start(*display_frame, Gtk::PACK_SHRINK);

        // Button grid with better spacing
        Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());
        grid->set_row_spacing(12);
        grid->set_column_spacing(12);
        grid->set_margin_top(15);
        grid->set_row_homogeneous(true);
        grid->set_column_homogeneous(true);
        main_box->pack_start(*grid, Gtk::PACK_EXPAND_WIDGET);

        // Create buttons with improved layout
        create_buttons(grid);

        apply_modern_styles();
        show_all_children();
    }

    // Add keyboard input handler
    bool on_key_press(GdkEventKey* event) {
        std::string key = "";

        switch (event->keyval) {
            case GDK_KEY_0: case GDK_KEY_KP_0: key = "0"; break;
            case GDK_KEY_1: case GDK_KEY_KP_1: key = "1"; break;
            case GDK_KEY_2: case GDK_KEY_KP_2: key = "2"; break;
            case GDK_KEY_3: case GDK_KEY_KP_3: key = "3"; break;
            case GDK_KEY_4: case GDK_KEY_KP_4: key = "4"; break;
            case GDK_KEY_5: case GDK_KEY_KP_5: key = "5"; break;
            case GDK_KEY_6: case GDK_KEY_KP_6: key = "6"; break;
            case GDK_KEY_7: case GDK_KEY_KP_7: key = "7"; break;
            case GDK_KEY_8: case GDK_KEY_KP_8: key = "8"; break;
            case GDK_KEY_9: case GDK_KEY_KP_9: key = "9"; break;
            case GDK_KEY_period: case GDK_KEY_KP_Decimal: key = "."; break;
            case GDK_KEY_plus: case GDK_KEY_KP_Add: key = "+"; break;
            case GDK_KEY_minus: case GDK_KEY_KP_Subtract: key = "-"; break;
            case GDK_KEY_asterisk: case GDK_KEY_KP_Multiply: key = "×"; break;
            case GDK_KEY_slash: case GDK_KEY_KP_Divide: key = "÷"; break;
            case GDK_KEY_Return: case GDK_KEY_KP_Enter: case GDK_KEY_equal: key = "="; break;
            case GDK_KEY_BackSpace: key = "⌫"; break;
            case GDK_KEY_Delete: case GDK_KEY_Escape: key = "AC"; break;
            default: return false;
        }

        if (!key.empty()) {
            on_button_clicked(key);
            return true;
        }

        return false;
    }

protected:
    void create_buttons(Gtk::Grid* grid) {
        // Row 0: Clear and operators
        add_button(grid, "AC", 0, 0, 2, 1, "clear-button");
        add_button(grid, "⌫", 2, 0, 1, 1, "backspace-button");
        add_button(grid, "÷", 3, 0, 1, 1, "operator-button");

        // Row 1: Numbers and operators
        add_button(grid, "7", 0, 1, 1, 1, "number-button");
        add_button(grid, "8", 1, 1, 1, 1, "number-button");
        add_button(grid, "9", 2, 1, 1, 1, "number-button");
        add_button(grid, "×", 3, 1, 1, 1, "operator-button");

        // Row 2
        add_button(grid, "4", 0, 2, 1, 1, "number-button");
        add_button(grid, "5", 1, 2, 1, 1, "number-button");
        add_button(grid, "6", 2, 2, 1, 1, "number-button");
        add_button(grid, "-", 3, 2, 1, 1, "operator-button");

        // Row 3
        add_button(grid, "1", 0, 3, 1, 1, "number-button");
        add_button(grid, "2", 1, 3, 1, 1, "number-button");
        add_button(grid, "3", 2, 3, 1, 1, "number-button");
        add_button(grid, "+", 3, 3, 1, 1, "operator-button");

        // Row 4
        add_button(grid, "0", 0, 4, 2, 1, "number-button-wide");
        add_button(grid, ".", 2, 4, 1, 1, "number-button");
        add_button(grid, "=", 3, 4, 1, 1, "equals-button");
    }

    void add_button(Gtk::Grid* grid, const std::string& label, int col, int row, int width, int height, const std::string& css_class) {
        Gtk::Button* button = Gtk::manage(new Gtk::Button(label));
        button->set_size_request(80, 60);
        button->signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this, &CalculatorWindow::on_button_clicked), label));
        button->get_style_context()->add_class(css_class);
        grid->attach(*button, col, row, width, height);
    }

    void on_button_clicked(const std::string& label) {
        if (label == "AC") {
            clear_all();
            return;
        }

        if (label == "⌫") {
            backspace();
            return;
        }

        if (label == "=") {
            calculate_result();
            return;
        }

        if (is_operator(label)) {
            handle_operator(label);
            return;
        }

        if (label == ".") {
            handle_decimal();
            return;
        }

        // Handle number input
        handle_number(label);
    }

    void handle_number(const std::string& number) {
        if (should_clear_display) {
            current_display = "";
            should_clear_display = false;
        }

        if (current_display == "0" && number != "0") {
            current_display = number;
        } else if (current_display != "0") {
            current_display += number;
        }

        update_display();
    }

    void handle_decimal() {
        if (should_clear_display) {
            current_display = "0";
            should_clear_display = false;
        }

        // Check if current number already has decimal point
        std::string current_number = get_current_number();
        if (current_number.find('.') == std::string::npos) {
            current_display += ".";
            update_display();
        }
    }

    void handle_operator(const std::string& op) {
        if (has_pending_operation) {
            calculate_result();
        }

        std::string normalized_op = normalize_operator(op);

        if (!current_display.empty()) {
            operand1 = std::stod(get_current_number());
            current_operator = normalized_op;
            has_pending_operation = true;
            should_clear_display = true;

            // Show the operation in display
            std::string display_text = format_number(operand1) + " " + op;
            m_display->set_text(display_text);
        }
    }

    void calculate_result() {
        if (has_pending_operation && !current_display.empty()) {
            double operand2 = std::stod(get_current_number());
            double result = perform_operation(operand1, operand2, current_operator);

            current_display = format_number(result);
            update_display();

            // Reset state
            has_pending_operation = false;
            should_clear_display = true;
            current_operator.clear();
        }
    }

    void clear_all() {
        current_display = "0";
        operand1 = 0.0;
        current_operator.clear();
        has_pending_operation = false;
        should_clear_display = false;
        update_display();
    }

    void backspace() {
        if (current_display.length() > 1) {
            current_display = current_display.substr(0, current_display.length() - 1);
        } else {
            current_display = "0";
        }
        update_display();
    }

    std::string get_current_number() {
        if (current_display.empty()) return "0";
        return current_display;
    }

    void update_display() {
        m_display->set_text(current_display);
    }

    std::string format_number(double number) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(10) << number;
        std::string str = oss.str();

        // Remove trailing zeros after decimal point
        if (str.find('.') != std::string::npos) {
            str = str.substr(0, str.find_last_not_of('0') + 1);
            if (str.find('.') == str.size() - 1) {
                str = str.substr(0, str.size() - 1);
            }
        }
        return str;
    }

    double perform_operation(double op1, double op2, const std::string& op) {
        if (op == "+") return op1 + op2;
        if (op == "-") return op1 - op2;
        if (op == "*") return op1 * op2;
        if (op == "/") return (op2 != 0) ? op1 / op2 : 0.0;
        return 0.0;
    }

    bool is_operator(const std::string& label) {
        return label == "+" || label == "-" || label == "×" || label == "÷";
    }

    std::string normalize_operator(const std::string& op) {
        if (op == "×") return "*";
        if (op == "÷") return "/";
        return op;
    }

    void apply_modern_styles() {
        auto css = Gtk::CssProvider::create();
        css->load_from_data(
            "window {"
            "   background-color: #2c2f36;"
            "}"
            ""
            "entry {"
            "   font-size: 32px;"
            "   font-weight: bold;"
            "   color: #2c3e50;"
            "   padding: 18px;"
            "   background-color: #ffffff;"
            "   border: 2px solid #4ecdc4;"
            "   border-radius: 8px;"
            "}"
            ""
            "button {"
            "   font-size: 20px;"
            "   font-weight: bold;"
            "   border-radius: 12px;"
            "   border: none;"
            "   padding: 15px;"
            "   transition: background-color 0.15s ease;"
            "}"
            ""
            "button.number-button, button.number-button-wide {"
            "   background-color: #f8f9fa;"
            "   color: #2c3e50;"
            "}"
            ""
            "button.number-button:hover, button.number-button-wide:hover {"
            "   background-color: #e9ecef;"
            "}"
            ""
            "button.operator-button {"
            "   background-color: #4ecdc4;"
            "   color: #4ecdc4;"
            "}"
            ""
            "button.operator-button:hover {"
            "   background-color: #45b7aa;"
            "}"
            ""
            "button.equals-button {"
            "   background-color: #ff6b6b;"
            "   color: #4ecdc4;"
            "}"
            ""
            "button.equals-button:hover {"
            "   background-color: #ff5252;"
            "}"
            ""
            "button.clear-button {"
            "   background-color: #ffa726;"
            "   color: #4ecdc4;"
            "}"
            ""
            "button.clear-button:hover {"
            "   background-color: #ff9800;"
            "}"
            ""
            "button.backspace-button {"
            "   background-color: #9575cd;"
            "   color: #4ecdc4;"
            "   font-size: 18px;"
            "}"
            ""
            "button.backspace-button:hover {"
            "   background-color: #7e57c2;"
            "}"
        );

        get_style_context()->add_provider_for_screen(
            Gdk::Screen::get_default(),
            css,
            GTK_STYLE_PROVIDER_PRIORITY_USER
        );
    }

private:
    Gtk::Entry* m_display;
    std::string current_display = "0";
    double operand1 = 0.0;
    std::string current_operator;
    bool has_pending_operation = false;
    bool should_clear_display = false;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.modern.calculator");
    CalculatorWindow window;
    return app->run(window);
}
