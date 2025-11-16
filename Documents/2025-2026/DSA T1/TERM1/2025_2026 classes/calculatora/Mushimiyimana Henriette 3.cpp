#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "Mushimiyimana Henriette 2.h"

double first_num = 0.0;
char current_op = '\0';
gboolean operator_clicked = FALSE;

void on_digit_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *display = GTK_ENTRY(user_data);
    const char *current_text = gtk_entry_get_text(display);
    const char *digit = gtk_button_get_label(GTK_BUTTON(widget));
    char new_text[256];

    if (operator_clicked) {
        snprintf(new_text, sizeof(new_text), "%s", digit);
        operator_clicked = FALSE;
    } else {
        if (strcmp(current_text, "0") == 0)
            snprintf(new_text, sizeof(new_text), "%s", digit);
        else
            snprintf(new_text, sizeof(new_text), "%s%s", current_text, digit);
    }
    gtk_entry_set_text(display, new_text);
}

void on_dot_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *display = GTK_ENTRY(user_data);
    const char *current_text = gtk_entry_get_text(display);

    if (strchr(current_text, '.') == NULL) { 
        char new_text[256];
        snprintf(new_text, sizeof(new_text), "%s.", current_text);
        gtk_entry_set_text(display, new_text);
    }
}

void on_operator_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *display = GTK_ENTRY(user_data);
    double current_num = atof(gtk_entry_get_text(display));

    if (current_op != '\0') {
        switch (current_op) {
            case '+': first_num = add(first_num, current_num); break;
            case '-': first_num = subtract(first_num, current_num); break;
            case '*': first_num = multiply(first_num, current_num); break;
            case '/': first_num = divide(first_num, current_num); break;
        }
        char result_text[256];
        snprintf(result_text, sizeof(result_text), "%g", first_num);
        gtk_entry_set_text(display, result_text);
    } else {
        first_num = current_num; 
    }

    current_op = gtk_button_get_label(GTK_BUTTON(widget))[0];

    gtk_entry_set_text(display, "");
}

void on_equal_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *display = GTK_ENTRY(user_data);
    double second_num = atof(gtk_entry_get_text(display));
    double result = 0.0;
    switch (current_op) {
        case '+': result = add(first_num, second_num); break;
        case '-': result = subtract(first_num, second_num); break;
        case '*': result = multiply(first_num, second_num); break;
        case '/':
	    if (second_num == 0) {
	        gtk_entry_set_text(display, "Error");
	        return;
	    } else {
	        result = divide(first_num, second_num);
	    }
	    break;

        default: result = second_num;
    }

    char result_text[256];
    snprintf(result_text, sizeof(result_text), "%g", result);
    gtk_entry_set_text(display, result_text);

    first_num = result;
    operator_clicked = TRUE;
}

void on_clear_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *display = GTK_ENTRY(user_data);
    gtk_entry_set_text(display, "0");
    first_num = 0.0;
    current_op = '\0';
    operator_clicked = FALSE;
}

	gboolean on_key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
	    GtkEntry *display = GTK_ENTRY(user_data);
	    char key = event->string[0]; 
	
	    if ((key >= '0' && key <= '9') || key == '.') {
	        const char *current_text = gtk_entry_get_text(display);
	        char new_text[256];
	        if (strcmp(current_text, "0") == 0)
	            snprintf(new_text, sizeof(new_text), "%c", key);
	        else
	            snprintf(new_text, sizeof(new_text), "%s%c", current_text, key);
	        gtk_entry_set_text(display, new_text);
	    } 
	    else if (key == '+' || key == '-' || key == '*' || key == '/') {
	        first_num = atof(gtk_entry_get_text(display));
	        current_op = key;
	        gtk_entry_set_text(display, "");
	    } 
	    else if (key == '=' || key == '\r') { 
	        double second_num = atof(gtk_entry_get_text(display));
	        double result = 0.0;
	        switch (current_op) {
	            case '+': result = add(first_num, second_num); break;
	            case '-': result = subtract(first_num, second_num); break;
	            case '*': result = multiply(first_num, second_num); break;
	            case '/': result = divide(first_num, second_num); break;
	            default: result = second_num;
	        }
	        char result_text[256];
	        snprintf(result_text, sizeof(result_text), "%g", result);
	        gtk_entry_set_text(display, result_text);
	    } 
	    else if (key == 'c' || key == 'C') {
	        gtk_entry_set_text(display, "0");
	        first_num = 0.0;
	        current_op = '\0';
	    }
	    return TRUE; 
	}
	
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Henriette's calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *display = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(display), "0");
    gtk_editable_set_editable(GTK_EDITABLE(display), FALSE);

    gtk_grid_attach(GTK_GRID(grid), display, 0, 0, 4, 1);
	gtk_widget_set_can_focus(window, TRUE);
	gtk_widget_grab_focus(window);
	g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_pressed), display);
    
    GtkWidget *btns[10];
    for (int i = 0; i <= 9; i++) {
        char label[2];
        snprintf(label, sizeof(label), "%d", i);
        btns[i] = gtk_button_new_with_label(label);
    }

    GtkWidget *btnDot = gtk_button_new_with_label(".");
    GtkWidget *btnEqual = gtk_button_new_with_label("=");
    GtkWidget *btnAdd = gtk_button_new_with_label("+");
    GtkWidget *btnSub = gtk_button_new_with_label("-");
    GtkWidget *btnMul = gtk_button_new_with_label("*");
    GtkWidget *btnDiv = gtk_button_new_with_label("/");
    GtkWidget *btnClear = gtk_button_new_with_label("C");
    
    gtk_grid_attach(GTK_GRID(grid), btns[7], 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btns[8], 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btns[9], 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnDiv, 3, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btns[4], 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btns[5], 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btns[6], 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnMul, 3, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btns[1], 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btns[2], 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btns[3], 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnSub, 3, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btns[0], 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnDot, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnEqual, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnAdd, 3, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btnClear, 0, 5, 4, 1);

    for (int i = 0; i <= 9; i++) {
        g_signal_connect(btns[i], "clicked", G_CALLBACK(on_digit_clicked), display);
    }
    g_signal_connect(btnDot, "clicked", G_CALLBACK(on_dot_clicked), display);
    g_signal_connect(btnAdd, "clicked", G_CALLBACK(on_operator_clicked), display);
    g_signal_connect(btnSub, "clicked", G_CALLBACK(on_operator_clicked), display);
    g_signal_connect(btnMul, "clicked", G_CALLBACK(on_operator_clicked), display);
    g_signal_connect(btnDiv, "clicked", G_CALLBACK(on_operator_clicked), display);
    g_signal_connect(btnEqual, "clicked", G_CALLBACK(on_equal_clicked), display);
    g_signal_connect(btnClear, "clicked", G_CALLBACK(on_clear_clicked), display);
    
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Mushimiyimana Henriette 4.css", NULL);
    gtk_style_context_add_provider_for_screen(
    gdk_screen_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_USER
    );
     GtkStyleContext *context;
     
	for (int i = 0; i <= 9; i++) {
	    GtkStyleContext *ctx = gtk_widget_get_style_context(btns[i]);
	    gtk_style_context_add_class(ctx, "button-number");
	}
	GtkStyleContext *ctxDot = gtk_widget_get_style_context(btnDot);
	gtk_style_context_add_class(ctxDot, "button-number");

	context = gtk_widget_get_style_context(btnAdd); gtk_style_context_add_class(context, "button-operator");
	context = gtk_widget_get_style_context(btnSub); gtk_style_context_add_class(context, "button-operator");
	context = gtk_widget_get_style_context(btnMul); gtk_style_context_add_class(context, "button-operator");
	context = gtk_widget_get_style_context(btnDiv); gtk_style_context_add_class(context, "button-operator");
	
	context = gtk_widget_get_style_context(btnClear); gtk_style_context_add_class(context, "button-clear");

	context = gtk_widget_get_style_context(btnEqual); gtk_style_context_add_class(context, "button-equal");
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
