#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <string>
#include <sstream>

Fl_Output *display;
std::string currentInput = "";


void update_display() {
    display->value(currentInput.c_str());
}

void button_cb(Fl_Widget* w, void* data) {
    std::string val = (char*)data;

    if (val == "C") {
        currentInput.clear();
        display->value("0");
    } else if (val == "=") {
        try {
            std::istringstream iss(currentInput);
            double result;
            iss >> result;
            char op;
            double num;
            while (iss >> op >> num) {
                if (op == '+') result += num;
                else if (op == '-') result -= num;
                else if (op == '*') result *= num;
                else if (op == '/') {
                    if (num == 0) { currentInput = "Can't divide by 0"; update_display(); return; }
                    result /= num;
                }
            }
            std::ostringstream oss;
            oss.precision(12);
            oss << result;
            currentInput = oss.str();
        } catch (...) {
            currentInput = "Error";
        }
        update_display();
    } else {
        currentInput += val;
        update_display();
    }
}

int main() {
    const int btnSize = 70;
    const int spacing = 10;
    const int offsetX = 20;
    const int offsetY = 120;

    Fl_Window *window = new Fl_Window(340, 520, "Modern Calculator");
    window->color(fl_rgb_color(30, 30, 30));

    display = new Fl_Output(offsetX, 20, 4*btnSize + 3*spacing, 80);
    display->box(FL_UP_BOX);
    display->color(fl_rgb_color(20, 20, 20));
    display->textfont(FL_HELVETICA_BOLD);
    display->textcolor(FL_WHITE);
    display->textsize(38);
    display->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    display->value("0");

    const char* labels[5][4] = {
        {"C", "/", "*", "-"},
        {"7", "8", "9", "+"},
        {"4", "5", "6", "="},
        {"1", "2", "3",""},
        {"0", ".", "",""}
    };

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 4; c++) {
            if (labels[r][c][0] == '\0') continue;

            Fl_Button *btn = new Fl_Button(offsetX + c*(btnSize + spacing),
                                           offsetY + r*(btnSize + spacing),
                                           btnSize, btnSize, labels[r][c]);
            btn->box(FL_FLAT_BOX);
            btn->color(fl_rgb_color(50, 50, 50));
            btn->selection_color(fl_rgb_color(100, 100, 100)); 
            btn->labelcolor(FL_WHITE);
            btn->labelfont(FL_HELVETICA_BOLD);
            btn->labelsize(28);

            btn->color(fl_rgb_color(50,50,50));

            if (labels[r][c][0] == 'C') btn->color(fl_rgb_color(220, 50, 50));
            else if (labels[r][c][0] == '=') btn->color(fl_rgb_color(180, 180, 180));
            else if (labels[r][c][0]=='+'||labels[r][c][0]=='-'||labels[r][c][0]=='*'||labels[r][c][0]=='/')
                btn->color(fl_rgb_color(70, 70, 70));

            btn->callback(button_cb, (void*)labels[r][c]);
        }
    }

    window->end();
    window->show();
    return Fl::run();
}
