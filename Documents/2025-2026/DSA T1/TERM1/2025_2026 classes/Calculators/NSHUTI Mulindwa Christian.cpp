#include <wx/wx.h>
#include <string>

class CalculatorApp : public wxApp {
public:
    virtual bool OnInit();
};

class CalculatorFrame : public wxFrame {
public:
    CalculatorFrame(const wxString& title);

private:
    wxTextCtrl* display;
    wxString currentInput;
    double firstOperand;
    wxString operation;

    void OnDigit(wxCommandEvent& event);
    void OnOperation(wxCommandEvent& event);
    void OnEquals(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnSquare(wxCommandEvent& event);
    void OnSqrt(wxCommandEvent& event);
};

enum {
    ID_DISPLAY = 1000,
    ID_BTN0,ID_BTN1,ID_BTN2,ID_BTN3,ID_BTN4,
    ID_BTN5,ID_BTN6,ID_BTN7,ID_BTN8,ID_BTN9,
    ID_ADD, ID_SUB,ID_MUL,ID_DIV,ID_EQ,ID_CLEAR,ID_SQRT,ID_SQUARE
};

IMPLEMENT_APP(CalculatorApp)

bool CalculatorApp::OnInit() {
    CalculatorFrame* frame = new CalculatorFrame("Christian's Calculator");
    frame->Show(true);
    return true;
}

CalculatorFrame::CalculatorFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY,title, wxDefaultPosition, wxSize(300,400))
    {
        wxPanel* panel = new wxPanel(this,wxID_ANY);

        display = new wxTextCtrl(panel,ID_DISPLAY,"",wxPoint(10,10),wxSize(260,40),
                                    wxTE_RIGHT | wxTE_READONLY);

        wxGridSizer* grid = new wxGridSizer(5,4,5,5);

        wxButton* buttons[18] = {
            new wxButton(panel,ID_BTN7, "7"),
            new wxButton(panel, ID_BTN8, "8"),
            new wxButton(panel, ID_BTN9, "9"),
            new wxButton(panel, ID_DIV, "/"),

            new wxButton(panel,ID_BTN4, "4"),
            new wxButton(panel,ID_BTN5, "5"),
            new wxButton(panel,ID_BTN6,"6"),
            new wxButton(panel, ID_MUL, "*"),

            new wxButton(panel, ID_BTN1, "1"),
            new wxButton(panel, ID_BTN2, "2"),
            new wxButton(panel, ID_BTN3, "3"),
            new wxButton(panel, ID_SUB,"-"),

            new wxButton(panel,ID_BTN0,"0"),
            new wxButton(panel,ID_CLEAR,"C"),
            new wxButton(panel,ID_EQ,"="),
            new wxButton(panel,ID_ADD, "+"),

            new wxButton(panel,ID_SQUARE,"x^2"),
            new wxButton(panel,ID_SQRT, "sqrt(x)"),
        };

        for (int i = 0;i < 18; i++) grid->Add(buttons[i],1,wxEXPAND);

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(display,0,wxEXPAND | wxALL, 5);
        vbox->Add(grid,1,wxEXPAND | wxALL, 5);

        panel->SetSizer(vbox);

        Bind(wxEVT_BUTTON,&CalculatorFrame::OnDigit,this,ID_BTN0,ID_BTN9);
        Bind(wxEVT_BUTTON, &CalculatorFrame::OnOperation,this,ID_ADD,ID_DIV);
        Bind(wxEVT_BUTTON, &CalculatorFrame::OnClear,this,ID_CLEAR);
        Bind(wxEVT_BUTTON, &CalculatorFrame::OnEquals, this, ID_EQ);
        Bind(wxEVT_BUTTON, &CalculatorFrame::OnSquare, this, ID_SQUARE);
        Bind(wxEVT_BUTTON, &CalculatorFrame::OnSqrt, this, ID_SQRT);
    }

void CalculatorFrame::OnDigit(wxCommandEvent& event) {
    int id = event.GetId();
    int digit = id - ID_BTN0;
    currentInput += wxString::Format("%d",digit);
    display->SetValue(currentInput);
}

void CalculatorFrame::OnOperation(wxCommandEvent& event) {
    firstOperand = wxAtof(currentInput);
    currentInput.clear();

    switch (event.GetId()) {
        case ID_ADD: operation = "+";break;
        case ID_SUB: operation = "-";break;
        case ID_MUL: operation = "*";break;
        case ID_DIV: operation = "/";break;
    }
}

    void CalculatorFrame::OnEquals(wxCommandEvent& event) {
        double secondOperand = wxAtof(currentInput);
        double result = 0;

        if(operation == "+") result = firstOperand + secondOperand;
        else if(operation == "-") result = firstOperand - secondOperand;
        else if(operation == "*") result = firstOperand * secondOperand;
        else if(operation == "/" && secondOperand != 0) result = firstOperand / secondOperand;
        else result = 0;

        display->SetValue(wxString::Format("%g",result));
        currentInput = wxString::Format("%g",result);
    }

void CalculatorFrame::OnClear(wxCommandEvent& event) {
    currentInput.Clear();
    display->Clear();
    firstOperand = 0;
    operation.clear();
}

void CalculatorFrame::OnSquare(wxCommandEvent& event) {
    double value = wxAtof(currentInput);
    double result = value * value;
    currentInput = wxString::Format("%g",result);
    display->SetValue(currentInput);
}

void CalculatorFrame::OnSqrt(wxCommandEvent& event) {
    double value = wxAtof(currentInput);
    if(value >= 0) {
        double result = sqrt(value);
        currentInput = wxString::Format("%g", result);
        display->SetValue(currentInput);
    } else {
        display->SetValue("Error");
    }
}


