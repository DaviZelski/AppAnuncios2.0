#pragma once
#include <wx/wx.h>
#include <SFML/audio.hpp>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#define _CRT_SECURE_NO_WARNINGS

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	void OnButtonClicked(wxCommandEvent& evt);

	sf::Music announcementPlayer;

	wxDECLARE_EVENT_TABLE();

	

	wxDirDialog* dlg;
	//dialog para selecionar pasta. Interessant porém não é util no momento
	wxFileDialog* fdlg;

	wxPanel* mainPanel;

};

