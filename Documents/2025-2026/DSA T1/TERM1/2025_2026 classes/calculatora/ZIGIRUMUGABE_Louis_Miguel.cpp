#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Input.H>
#include <string>

Fl_Input* display;
std::string currentExpression = "";

void updateDisplay(){
    display->value(currentExpression.c_str());
}
void clear_cb(Fl_Widget*, void*){
   currentExpression = "";
   updateDisplay();
}

void btn_cb(Fl_Widget*w, void*data){
    const char* value = (const char*) data;
    currentExpression += value;
    updateDisplay();
}

void equal_cb(Fl_Widget* w, void*) {
    double a=0,b=0;
    char op= 0;
    if(sscanf(currentExpression.c_str(), "%lf %c %lf", &a, &op , &b) == 3) {
        double result = 0;
        switch(op) {
            case '+': result = a+b; break;
            case '-': result = a-b; break;
            case '*': result = a*b; break;
            case '/': result = (b!=0) ? a/b : 0 ; break;
        }
        currentExpression = std::to_string(result);
    }else {
        currentExpression = "Error";
    }
    updateDisplay();
}

int main(int argc, char** argv) {
    Fl_Window* win = new Fl_Window(250,300,"Calculator");
    display = new Fl_Input(20,20,210,30);
    display->readonly(1);

    const char* labels[4][4] = {
        {"7", "8", "9", "+"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "*"},
        {"C", "0", "=", "/"}
    };

    for(int rows = 0 ; rows<4 ; rows++) {
        for(int cols = 0 ; cols<4 ; cols++){
            int x = 20 + cols * 50;
            int y = 70 + rows * 50;
            Fl_Button* btn = new Fl_Button(x,y,40,40,labels[rows][cols]);

            if (strcmp(labels[rows][cols], "C") == 0) {
                btn->callback(clear_cb);
            } else if (strcmp(labels[rows][cols], "=") == 0) {
                btn->callback(equal_cb);
            } else {
                btn->callback(btn_cb, (void*)labels[rows][cols]);
            }

        }
    }

    win->end();
    win->show(argc,argv);
    return Fl::run();

}

// The calculator programs only runs when built with the appropriate tools 
// I cloned the vcpkg repo
// Installed the gui library with the help of vcpkg as package manager since it helped to install and build the gui library(FLTK) in one go.
// Then built the file into an executable.