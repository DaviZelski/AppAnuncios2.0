#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#define _CRT_SECURE_NO_WARNINGS

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("App Anúncios 2.0");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();

	return true;
}