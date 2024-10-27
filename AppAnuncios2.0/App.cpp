#include <wx/wx.h>
#include <thread>

#include "App.h"
#include "MainFrame.h"
#include "Main.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("App Anúncios 2.0");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();


	thread MainLoopThread(MainLogicLoop);
	MainLoopThread.detach();

	return true;
}