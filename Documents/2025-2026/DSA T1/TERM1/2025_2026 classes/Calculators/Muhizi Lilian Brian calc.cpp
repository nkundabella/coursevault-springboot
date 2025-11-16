#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <string>
#include <sstream>
#include <cstdint>
#include <cstdio>


Fl_Input *input;
Fl_Multiline_Output *history;
std::string current = "";
std::string historyText = "";


void calculate(Fl_Widget*, void*) {
    double a, b, result = 0;
    char op;
    if (sscanf(current.c_str(), "%lf%c%lf", &a, &op, &b) == 3) {
        switch(op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': if (b != 0) result = a / b; else { input->value("Error: /0"); return; } break;
            default: return;
        }
        std::string expression = current + " = " + std::to_string(result) + "\n";
        historyText += expression;
        history->value(historyText.c_str());
        current = std::to_string(result);
        input->value(current.c_str());
    }
}

void append(Fl_Widget*, void* v) {
    current += (char)(intptr_t)v;
    input->value(current.c_str());
}

void clearInput(Fl_Widget*, void*) {
    current = "";
    input->value("");
}

void eraseLast(Fl_Widget*, void*) {
    if (!current.empty()) {
        current.pop_back();
        input->value(current.c_str());
    }
}

void inputCallback(Fl_Widget* w, void*) {
    Fl_Input *inp = (Fl_Input*)w;
    std::string val = inp->value();
    current = val;   // take typed input
    calculate(nullptr, nullptr);
}

int handleKeys(int event) {
    if (event == FL_KEYDOWN) {
        int key = Fl::event_key();
        if (key == FL_Enter || key == FL_KP_Enter) { // Enter
            inputCallback(input, nullptr);
            return 1;
        }
        if (key == FL_BackSpace) { // Backspace
            eraseLast(nullptr, nullptr);
            return 1;
        }
    }
    return 0; 
}

int main(int argc, char **argv) {
    Fl_Window *win = new Fl_Window(340, 520, "Styled Calculator");

    input = new Fl_Input(20, 20, 300, 35, "");
    input->textsize(18);
    input->callback(inputCallback);

    history = new Fl_Multiline_Output(20, 65, 300, 100, "");
    history->textsize(14);

    int btnW = 65, btnH = 45, startX = 20, startY = 180, gap = 10;

    const char *labels[5][4] = {
    {"7", "8", "9", "/"},
    {"4", "5", "6", "*"},
    {"1", "2", "3", "-"},
    {"0", "C", "=", "+"},
    {"DEL", "", "", ""}  
};

for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 4; c++) {
        if (labels[r][c][0] == '\0') continue; 

        Fl_Button *b = new Fl_Button(startX + c*(btnW+gap), startY + r*(btnH+gap), btnW, btnH, labels[r][c]);
        b->labelsize(18);
        b->box(FL_ROUND_UP_BOX);   
        b->color(FL_LIGHT2);
        b->selection_color(FL_BLUE);

        if (strcmp(labels[r][c], "C") == 0) b->callback(clearInput);
        else if (strcmp(labels[r][c], "=") == 0) b->callback(calculate);
        else if (strcmp(labels[r][c], "DEL") == 0) {
            b->callback(eraseLast);
            b->label("⌫"); 
        }
        else b->callback(append, (void*)(intptr_t)labels[r][c][0]);
    }
}

    win->end();
    win->callback([](Fl_Widget*, void*){ exit(0); });
    win->show(argc, argv);

    Fl::add_handler(handleKeys); 
    return Fl::run();
}