#include "Cyizere-Happy_MainFrame.h"
#include "Cyizere-Happy_Calculator.h"

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 400)) {

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    m_display = new wxTextCtrl(panel, wxID_ANY, "",
        wxDefaultPosition, wxSize(-1, 60),
        wxTE_RIGHT | wxTE_READONLY);

    wxFont font(24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    m_display->SetFont(font);

    vbox->Add(m_display, 0, wxEXPAND | wxALL, 5);

    wxGridSizer* grid = new wxGridSizer(5, 4, 5, 5);

    wxString buttons[17] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+",
        "C"
    };

    for (int i = 0; i < 17; i++) {
        wxButton* btn = new wxButton(panel, 1000 + i, buttons[i]);
        grid->Add(btn, 1, wxEXPAND);
        btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
    }

    vbox->Add(grid, 1, wxEXPAND | wxALL, 5);
    panel->SetSizer(vbox);
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
    wxButton* btn = dynamic_cast<wxButton*>(evt.GetEventObject());
    wxString label = btn->GetLabel();

    static Calculator calc;

    if (label == "C") {
        m_display->Clear();
    }
    else if (label == "=") {
        wxString expr = m_display->GetValue();

        try {
            double result = calc.Evaluate(std::string(expr.mb_str()));
            m_display->SetValue(std::to_string(result));
        }
        catch (...) {
            m_display->SetValue("Error");
        }
    }
    else {
        // --- Prevent multiple operators in a row ---
        wxString current = m_display->GetValue();

        if (label == "+" || label == "-" || label == "*" || label == "/") {
            if (!current.IsEmpty()) {
                wxChar lastChar = current[current.Length() - 1];
                if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') {
                    // Replace the last operator instead of adding a new one
                    current.RemoveLast();
                    m_display->SetValue(current);
                }
            }
            else {
                // Prevent starting with *, /
                if (label == "*" || label == "/") return;
            }
        }

        m_display->AppendText(label);
    }
}

