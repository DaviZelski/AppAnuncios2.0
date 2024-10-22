#include "MainFrame.h"
#include <wx/wx.h>
#include "Anuncio.h"
#include <SFML/Audio.hpp>
#include <string>
#include <shellapi.h>
#include <Windows.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

enum IDs {
	PLAY_BUTTON = 2
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(PLAY_BUTTON, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE();

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	mainPanel = new wxPanel(this);

	wxButton* playButton = new wxButton(mainPanel, PLAY_BUTTON, "Tocar Anúncio", wxDefaultPosition, wxDefaultSize);

	

	CreateStatusBar();

}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	Anuncio* anuncio = new Anuncio;

	/*dlg = new wxDirDialog(mainPanel, "Escolha a pasta", "C:\\Users\\Davi\\Desktop\\avisos");
	dlg->ShowModal();
	dlg->GetPath();*/
	//apenas para selecionar pastas e retornar o caminho, vou deixar aqui pq vai ser util mais tarde

	fdlg = new wxFileDialog(mainPanel, "Escolha o anúncio", "C:\\Users\\Davi\\Desktop\\avisos");
	fdlg->ShowModal();

	wxString fPathConv = wxString::Format("%s", fdlg->GetCurrentlySelectedFilename());
	
	anuncio->SetFilePath(fPathConv);
	wxString pathVerify = wxString::Format("%s", anuncio->GetFilePath());

	if (!announcementPlayer.openFromFile(anuncio->GetFilePath())) {

		wxString string = wxString::Format("Caminho nao encontrado");
		wxLogStatus(string);

	}
	else {
		wxString string = wxString::Format("Caminho encontrado: %s", anuncio->GetFilePath());
		wxLogStatus(string);
	}


	announcementPlayer.play();
}

