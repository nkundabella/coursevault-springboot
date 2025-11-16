#include "app.h"
#include "Cyizere-Happy_MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App:: OnInit() {
	MainFrame* mainFrame = new MainFrame("Simple Calculator");
	mainFrame->Show();
	mainFrame->SetClientSize(500, 600);
	mainFrame->Center();
	return true;

}