#include <wx/wx.h>
#include <wx/gbsizer.h>

class CalculatorFrame : public wxFrame
{
    wxTextCtrl* display;
    wxString currentInput = "0", pendingOperation;
    double operand1 = 0;
    bool newInput = true;

    void UpdateDisplay() { display->SetValue(currentInput); }
    void Calculate()
    {
        double val = 0;
        if (!currentInput.ToDouble(&val)) return;
        if (pendingOperation.IsEmpty()) operand1 = val;
        else {
            if (pendingOperation == "+") operand1 += val;
            else if (pendingOperation == "-") operand1 -= val;
            else if (pendingOperation == "*") operand1 *= val;
            else if (pendingOperation == "/") {
                if (val == 0) { wxMessageBox("Cannot divide by zero", "Error", wxOK | wxICON_ERROR); ClearAll(); return; }
                operand1 /= val;
            }
            else if (pendingOperation == "%") operand1 = operand1 * (val / 100);
        }
        currentInput = wxString::Format("%.10g", operand1);
        pendingOperation.Clear();
        newInput = true;
        UpdateDisplay();
    }
    void ClearAll() { currentInput = "0"; operand1 = 0; pendingOperation.Clear(); newInput = true; UpdateDisplay(); }
    void Backspace() { if (!newInput && !currentInput.IsEmpty()) { currentInput.RemoveLast(); if (currentInput.IsEmpty()) currentInput = "0"; UpdateDisplay(); } }
    void AppendDot() { if (newInput) { currentInput = "0."; newInput = false; } else if (!currentInput.Contains('.')) currentInput += '.'; UpdateDisplay(); }
    void AppendDigit(const wxString& d)
    {
        if (newInput) currentInput = d, newInput = false;
        else if (!(d == "0" && currentInput == "0")) currentInput += d;
        UpdateDisplay();
    }

public:
    CalculatorFrame()
        : wxFrame(nullptr, wxID_ANY, "Simple Calculator", wxDefaultPosition, wxSize(320, 420))
    {
        auto panel = new wxPanel(this);
        panel->SetBackgroundColour(wxColour(20, 20, 20));
        display = new wxTextCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(-1, 70), wxTE_RIGHT | wxTE_READONLY | wxBORDER_NONE);
        display->SetFont(wxFont(28, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        display->SetBackgroundColour(wxColour(20, 20, 20));
        display->SetForegroundColour(*wxWHITE);

        struct Btn { wxString lbl; int r, c, rs, cs; };
        Btn btns[] = {
            {"C",0,0,1,1},{"←",0,1,1,1},{"±",0,2,1,1},{"/",0,3,1,1},
            {"7",1,0,1,1},{"8",1,1,1,1},{"9",1,2,1,1},{"*",1,3,1,1},
            {"4",2,0,1,1},{"5",2,1,1,1},{"6",2,2,1,1},{"-",2,3,1,1},
            {"1",3,0,1,1},{"2",3,1,1,1},{"3",3,2,1,1},{"+",3,3,1,1},
            {"0",4,0,1,2},{".",4,2,1,1},{"=",4,3,1,1}
        };

        auto grid = new wxGridBagSizer(5, 5);
        wxFont f(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

        for (auto& b : btns)
        {
            auto btn = new wxButton(panel, wxID_ANY, b.lbl);
            btn->SetFont(f);
            if (b.lbl == "+" || b.lbl == "-" || b.lbl == "*" || b.lbl == "/" || b.lbl == "=")
                btn->SetBackgroundColour(wxColour(255,149,0));
            else if (b.lbl == "C" || b.lbl == "←" || b.lbl == "±")
                btn->SetBackgroundColour(wxColour(165,165,165));
            else btn->SetBackgroundColour(wxColour(55,55,55));
            btn->SetForegroundColour(*wxWHITE);
#ifndef __WXMSW__
            btn->SetWindowStyleFlag(wxBORDER_NONE);
            btn->SetOwnBackgroundColour(btn->GetBackgroundColour());
#endif
            grid->Add(btn, wxGBPosition(b.r, b.c), wxGBSpan(b.rs, b.cs), wxEXPAND);
            btn->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton, this);
        }

        for (int i=0;i<4;++i) grid->AddGrowableCol(i,1);
        for (int i=0;i<5;++i) grid->AddGrowableRow(i,1);

        auto vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(display, 0, wxEXPAND | wxALL, 10);
        vbox->Add(grid, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel->SetSizer(vbox);
        Bind(wxEVT_CHAR_HOOK, &CalculatorFrame::OnKeyDown, this);
        UpdateDisplay();
    }

    void OnButton(wxCommandEvent& e)
    {
        auto btn = dynamic_cast<wxButton*>(e.GetEventObject());
        if (!btn) return;
        auto label = btn->GetLabel();
        if (label == "C") ClearAll();
        else if (label == "←") Backspace();
        else if (label == "±")
        {
            if (currentInput.StartsWith("-")) currentInput = currentInput.Mid(1);
            else if (currentInput != "0") currentInput = "-" + currentInput;
            UpdateDisplay();
        }
        else if (label == "+" || label == "-" || label == "*" || label == "/" || label == "%")
        {
            if (!pendingOperation.IsEmpty() && !newInput) Calculate();
            pendingOperation = label;
            currentInput.ToDouble(&operand1);
            newInput = true;
        }
        else if (label == "=") Calculate();
        else if (label == ".") AppendDot();
        else AppendDigit(label);
    }

    void OnKeyDown(wxKeyEvent& e)
    {
        int k = e.GetKeyCode();
        if (k >= '0' && k <= '9') AppendDigit(wxString::Format("%c", k));
        else switch (k)
            {
            case WXK_BACK: Backspace(); break;
            case WXK_ESCAPE: ClearAll(); break;
            case WXK_RETURN: case WXK_NUMPAD_ENTER: Calculate(); break;
            case '.': case WXK_NUMPAD_DECIMAL: AppendDot(); break;
            case '+': case WXK_NUMPAD_ADD:
                if (!pendingOperation.IsEmpty() && !newInput) Calculate();
                pendingOperation = "+"; currentInput.ToDouble(&operand1); newInput = true; break;
            case '-': case WXK_NUMPAD_SUBTRACT:
                if (!pendingOperation.IsEmpty() && !newInput) Calculate();
                pendingOperation = "-"; currentInput.ToDouble(&operand1); newInput = true; break;
            case '*': case WXK_NUMPAD_MULTIPLY:
                if (!pendingOperation.IsEmpty() && !newInput) Calculate();
                pendingOperation = "*"; currentInput.ToDouble(&operand1); newInput = true; break;
            case '/': case WXK_NUMPAD_DIVIDE:
                if (!pendingOperation.IsEmpty() && !newInput) Calculate();
                pendingOperation = "/"; currentInput.ToDouble(&operand1); newInput = true; break;
            case '%': {
                double val = 0; if (currentInput.ToDouble(&val)) { val /= 100; currentInput = wxString::Format("%.10g", val); UpdateDisplay(); }
                break; }
            default: e.Skip();
            }
    }
};

class CalculatorApp : public wxApp { public: bool OnInit() override { (new CalculatorFrame())->Show(); return true; } };

wxIMPLEMENT_APP(CalculatorApp);
