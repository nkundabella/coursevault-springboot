#include <gtkmm.h>
#include <string>
#include <sstream>
#include <iomanip>

class CalculatorWindow : public Gtk::Window {
public:
    CalculatorWindow();

private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::Entry display;
    Gtk::Grid grid;
    Glib::RefPtr<Gtk::CssProvider> cssProvider;

    double storedValue = 0.0;
    char pendingOp = 0;
    bool entering = false;
    std::string entry = "0";

    void on_button_clicked(const Glib::ustring& label);
    void update_display();
    bool apply_pending_op();
    void clear_all();
    void setup_styling();
    bool on_key_press_event(GdkEventKey* key_event) override;
};

CalculatorWindow::CalculatorWindow() {
    set_title("Calculator");
    set_default_size(360, 540);
    set_resizable(false);

    add(vbox);
    vbox.set_spacing(10);
    vbox.set_margin_top(12);
    vbox.set_margin_bottom(12);
    vbox.set_margin_start(12);
    vbox.set_margin_end(12);

    display.set_text(entry);
    display.set_editable(false);
    display.set_alignment(1.0);
    display.get_style_context()->add_class("display");
    vbox.pack_start(display, Gtk::PACK_SHRINK);

    grid.set_row_spacing(8);
    grid.set_column_spacing(8);
    grid.set_row_homogeneous(true);
    grid.set_column_homogeneous(true);

    const char* buttons[5][4] = {
        {"C", "CE", "÷", "×"},
        {"7", "8", "9", "-"},
        {"4", "5", "6", "+"},
        {"1", "2", "3", ""},
        {"+/-", "0", ".", "="}
    };

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 4; c++) {
            std::string lbl = buttons[r][c];
            if (lbl == "") continue;
            Gtk::Button* btn = Gtk::make_managed<Gtk::Button>(lbl);
            btn->set_hexpand(true);
            btn->set_vexpand(true);
            if (lbl == "C" || lbl == "CE") btn->get_style_context()->add_class("clear-button");
            else if (lbl == "+" || lbl == "-" || lbl == "×" || lbl == "÷" || lbl == "*" || lbl == "/") btn->get_style_context()->add_class("operation-button");
            else if (lbl == "=") btn->get_style_context()->add_class("equals-button");
            else btn->get_style_context()->add_class("number-button");
            grid.attach(*btn, c, r, 1, 1);
            btn->signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &CalculatorWindow::on_button_clicked), lbl));
        }
    }

    vbox.pack_start(grid);
    setup_styling();
    set_can_focus(true);
    grab_focus();
    show_all_children();
}

void CalculatorWindow::setup_styling() {
    cssProvider = Gtk::CssProvider::create();
    std::string css = R"(
        window {
            background-color: #242424;
        }
        .display {
            background-color: #0f0f0f;
            color: #ffffff;
            border: none;
            border-radius: 10px;
            padding: 18px 18px;
            font-size: 36px;
            font-family: "Segoe UI", "Helvetica Neue", Arial, sans-serif;
            min-height: 78px;
        }
        button {
          background-color: #1a1a1a;
          color: #ffffff;
                    border: none;
                    border-radius: 8px;
                    font-size: 20px;
                    font-family: "Segoe UI", "Helvetica Neue", Arial, sans-serif;
                    min-height: 56px;
                    min-width: 56px;
        }
    button:hover {
    background-color: #2a2a2a;
}
        .number-button {
            background-color: #1a1a1a;
        }
        .number-button:hover {
            background-color: #222222;
        }
        .operation-button {
            background-color: #1a1a1a;
        }
        .operation-button:hover {
            background-color: #222222;
        }
        .equals-button {
            background-color: #154a7a;
        }
        .equals-button:hover {
            background-color: #1b5f92;
        }
        .clear-button {
            background-color: #2b2b2b;
            color: #ffffff;
        }
        .clear-button:hover {
            background-color: #343434;
        }
    )";
    cssProvider->load_from_data(css);
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void CalculatorWindow::update_display() {
    display.set_text(entry);
}

void CalculatorWindow::clear_all() {
    entry = "0";
    storedValue = 0;
    pendingOp = 0;
    entering = false;
    update_display();
}

bool CalculatorWindow::apply_pending_op() {
    double right = 0;
    try { right = std::stod(entry); } catch(...) { entry = "Error"; update_display(); return false; }
    double result = storedValue;
    if (pendingOp == '+') result += right;
    else if (pendingOp == '-') result -= right;
    else if (pendingOp == '*') result *= right;
    else if (pendingOp == '/') {
        if (right == 0.0) { entry = "Error"; update_display(); return false; }
        result /= right;
    } else {
        result = right;
    }
    storedValue = result;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << result;
    std::string s = oss.str();
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (!s.empty() && s.back() == '.') s.pop_back();
    entry = s;
    update_display();
    return true;
}

void CalculatorWindow::on_button_clicked(const Glib::ustring& label) {
    std::string s = label;
    if (s == "C") { clear_all(); return; }
    if (s == "CE") { entry = "0"; entering = false; update_display(); return; }
    if (s == "=") { if (pendingOp) { apply_pending_op(); pendingOp = 0; entering = false; } return; }
    if (s == "+/-") { if (!entry.empty() && entry[0] == '-') entry.erase(0,1); else if (entry != "0") entry = "-" + entry; update_display(); return; }
    if (s == ".") { if (entry.find(".") == std::string::npos) { entry += "."; entering = true; update_display(); } return; }
    if (s == "+" || s == "-" || s == "×" || s == "÷" || s == "*" || s == "/") {
        if (entering && pendingOp) apply_pending_op();
        storedValue = std::stod(entry);
        if (s == "×" || s == "*") pendingOp = '*';
        else if (s == "÷" || s == "/") pendingOp = '/';
        else pendingOp = s[0];
        entering = false;
        return;
    }
    if (!s.empty() && isdigit(s[0])) {
        if (!entering || entry == "0") entry = s; else entry += s;
        entering = true;
        update_display();
        return;
    }
}

bool CalculatorWindow::on_key_press_event(GdkEventKey* key_event) {
    guint key = key_event->keyval;
    if (key >= GDK_KEY_0 && key <= GDK_KEY_9) {
        std::string digit = std::to_string(key - GDK_KEY_0);
        on_button_clicked(digit);
        return true;
    }
    switch (key) {
        case GDK_KEY_plus:
        case GDK_KEY_KP_Add:
            on_button_clicked("+"); return true;
        case GDK_KEY_minus:
        case GDK_KEY_KP_Subtract:
            on_button_clicked("-"); return true;
        case GDK_KEY_asterisk:
        case GDK_KEY_KP_Multiply:
            on_button_clicked("*"); return true;
        case GDK_KEY_slash:
        case GDK_KEY_KP_Divide:
            on_button_clicked("/"); return true;
        case GDK_KEY_equal:
        case GDK_KEY_KP_Enter:
        case GDK_KEY_Return:
            on_button_clicked("="); return true;
        case GDK_KEY_period:
        case GDK_KEY_KP_Decimal:
            on_button_clicked("."); return true;
        case GDK_KEY_BackSpace:
        case GDK_KEY_Delete:
            on_button_clicked("CE"); return true;
        case GDK_KEY_Escape:
            clear_all(); return true;
    }
    return Gtk::Window::on_key_press_event(key_event);
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.calculator");
    CalculatorWindow win;
    return app->run(win);
}