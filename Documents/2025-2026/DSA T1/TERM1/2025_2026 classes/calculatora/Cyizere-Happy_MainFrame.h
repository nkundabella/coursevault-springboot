#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    wxTextCtrl* m_display;

    void OnButtonClicked(wxCommandEvent& evt);
};
