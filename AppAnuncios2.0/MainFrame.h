#pragma once
#include <wx/wx.h>
#include <wx/menu.h>
#include <SFML/audio.hpp>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/spinctrl.h>
#define _CRT_SECURE_NO_WARNINGS

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);

	void SetFolderPath(wxString SetfPath) {
		folderPath = SetfPath;
	}
	
	wxString getFolderPath() {
		return folderPath;
	}

private:
	void OnButtonClicked(wxCommandEvent& evt);
	void SetMainFolder(wxCommandEvent& evt);

	sf::Music announcementPlayer;

	wxDECLARE_EVENT_TABLE();

	wxString folderPath;

	wxMenuBar* menuBar;
	wxMenu* fileMenu;
	wxSpinCtrl* loopControl;
	wxDirDialog* ddlg;
	//dialog para selecionar pasta. Interessant porém não é util no momento
	wxFileDialog* fdlg;
	wxButton* playButton;
	wxSlider* volumeSlider;
	wxPanel* mainPanel;

};

