#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <string>
#include <sstream>

using namespace std;

Fl_Input *input;
int firstNumber = 0;
int secondNumber = 0;
char operation = '\0';
bool newInput = true;

void setInput(const string &text) {
    input->value(text.c_str());
}

void digit_cb(Fl_Widget* w, void*) {
    Fl_Button* btn = (Fl_Button*)w;
    string value = btn->label();
    if (newInput) {
        setInput(value);
        newInput = false;
    } else {
        string current = input->value();
        setInput(current + value);
    }
}

void op_cb(Fl_Widget* w, void*) {
    Fl_Button* btn = (Fl_Button*)w;
    firstNumber = stoi(input->value());
    operation = btn->label()[0];
    newInput = true;
}

void equal_cb(Fl_Widget*, void*) {
    secondNumber = stoi(input->value());
    int result = 0;
    bool error = false;

    switch (operation) {
        case '+': result = firstNumber + secondNumber; break;
        case '-': result = firstNumber - secondNumber; break;
        case '*': result = firstNumber * secondNumber; break;
        case '/':
            if (secondNumber == 0) { error = true; break; }
            result = firstNumber / secondNumber; break;
        case '%':
            if (secondNumber == 0) { error = true; break; }
            result = firstNumber % secondNumber; break;
        default: return;
    }

    if (error) {
        setInput("Error");
    } else {
        setInput(to_string(result));
    }
    newInput = true;
}

void clear_cb(Fl_Widget*, void*) {
    setInput("");
    firstNumber = secondNumber = 0;
    operation = '\0';
    newInput = true;
}

int main() {
    Fl_Window *window = new Fl_Window(300, 400, "FLTK Calculator");

    input = new Fl_Input(10, 10, 280, 40);
    input->align(FL_ALIGN_RIGHT);

    int x = 10, y = 60, w = 60, h = 60;
    for (int i = 1; i <= 9; ++i) {
        Fl_Button *btn = new Fl_Button(x, y, w, h, to_string(i).c_str());
        btn->callback(digit_cb);
        x += 70;
        if (i % 3 == 0) { x = 10; y += 70; }
    }

    Fl_Button *zero = new Fl_Button(10, 280, 60, 60, "0");
    zero->callback(digit_cb);

    Fl_Button *clear = new Fl_Button(80, 280, 60, 60, "C");
    clear->callback(clear_cb);

    Fl_Button *equal = new Fl_Button(150, 280, 60, 60, "=");
    equal->callback(equal_cb);

    const char* ops[5] = {"+", "-", "*", "/", "%"};
    y = 60;
    for (int i = 0; i < 5; ++i) {
        Fl_Button *btn = new Fl_Button(220, y, 60, 60, ops[i]);
        btn->callback(op_cb);
        y += 70;
    }

    window->end();
    window->show();
    return Fl::run();
}
