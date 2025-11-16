#include <gtk/gtk.h>
#include <string>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if(b!=0){
                return  a / b ;
            }else{
                return 0;
            }

    }
    return 0;
}
double expressionEvaluator(const string &tokens) {
    stack<double> values;
    stack<char> ops;

    for (size_t i = 0; i < tokens.length(); i++) {
        if (tokens[i] == ' ') continue;

        if (isdigit(tokens[i])) {
            double val = 0;
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
            i--;
            values.push(val);
        }
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(val1, val2, op));
            }
            if (!ops.empty()) ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperator(val1, val2, op));
    }
    return values.top();
}
static void onButtonClickk(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget**)data;
    GtkEntry *entry = GTK_ENTRY(widgets[0]);
    GtkLabel *result_label = GTK_LABEL(widgets[1]);

    const char *text = gtk_button_get_label(GTK_BUTTON(widget));
    string current = gtk_entry_get_text(entry);

    if (string(text) == "=") {
        if (!current.empty()) {
            double result = expressionEvaluator(current);
            ostringstream out;
            out << result;
            gtk_label_set_text(result_label, out.str().c_str());
        }
    }
    else if (string(text) == "C") {
        gtk_entry_set_text(entry, "");
        gtk_label_set_text(result_label, "");
    }
    else {
        current += text;
        gtk_entry_set_text(entry, current.c_str());
    }
}
int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *entry, *label, *vbox;
    const char *buttons[4][5] = {
        {"7", "8", "9", "/", "("},
        {"4", "5", "6", "*", ")"},
        {"1", "2", "3", "-", "C"},
        {"0", ".", "=", "+", ""}
    };

    gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "C++ GTK Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);


    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);


    entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE); // disable typing, only buttons
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);


    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 5);

    GtkWidget *widgets[2] = { entry, label };


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (buttons[i][j][0] == '\0') continue; // skip empty slot
            GtkWidget *btn = gtk_button_new_with_label(buttons[i][j]);
            gtk_grid_attach(GTK_GRID(grid), btn, j, i, 1, 1);
            g_signal_connect(btn, "clicked", G_CALLBACK(onButtonClickk), widgets);
        }
    }


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}