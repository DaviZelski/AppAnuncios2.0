#include <wx/wx.h>
#include <SFML/Audio.hpp>
#include <string>
#include <shellapi.h>
#include <Windows.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <thread>
#include <memory>
#include <wx/spinctrl.h>

#include "MainFrame.h"
#include "Anuncio.h"
#include "Main.h"
#define _CRT_SECURE_NO_WARNINGS


enum IDs {
	PLAY_BUTTON = 2,
	LOOP_CONTROL = 3,
	VOLUME_SLIDER = 4,
	FILE_MENU = 5,
	SET_FOLDER = 6
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(PLAY_BUTTON, MainFrame::OnButtonClicked)
	EVT_MENU(SET_FOLDER, MainFrame::SetMainFolder)
wxEND_EVENT_TABLE();

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
	
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0x57, 0x65, 0x6b)); // wxColour(0xXX, 0xXX, 0xXX) usar hexadecimal para mudar a cor, vou deixar cinza por enquanto
	
	menuBar = new wxMenuBar();
	fileMenu = new wxMenu();
	wxMenuItem* setFolder = new wxMenuItem(fileMenu, SET_FOLDER, "Escolher pasta de avisos");
	fileMenu->Append(setFolder);

	menuBar->Append(fileMenu, _("&Arquivos"));
	SetMenuBar(menuBar);

	playButton = new wxButton(mainPanel, PLAY_BUTTON, "Tocar Anúncio", wxPoint(100, 100), wxDefaultSize);
	
	wxStaticText* lCtrlTxt = new wxStaticText(mainPanel, wxID_ANY, "Quantidade de loops", wxPoint(220, 80));
	loopControl = new wxSpinCtrl(mainPanel, LOOP_CONTROL, "", wxPoint(250, 100), wxDefaultSize, wxSP_WRAP, 1, 10, 1);
	
	wxStaticText* sSldTxt = new wxStaticText(mainPanel, wxID_ANY, "Volume da música", wxPoint(360, 80));
	volumeSlider = new wxSlider(mainPanel, VOLUME_SLIDER, 17, 0, 100, wxPoint(370, 100), wxDefaultSize, wxSL_VALUE_LABEL);


	CreateStatusBar();

	
	
}

//TENTAR IMPLEMENTAR TEXTO PARA FALA COM https://github.com/rhasspy/piper


void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	Anuncio* anuncio = new Anuncio;

	

	anuncio->setLoopCount(loopControl->GetValue());
	anuncio->setBckgrMusicVol(volumeSlider->GetValue());

	wxString aFpath;


	fdlg = new wxFileDialog(mainPanel, "Escolha o anúncio", getFolderPath());
	if (fdlg->ShowModal() == wxID_CANCEL) {
		return;  
	}

	

	wxString fPathConv = wxString::Format("%s", fdlg->GetPath());
	anuncio->SetFilePath(fPathConv);

	thread anuncioThread(TocarAnuncio, anuncio);
	anuncioThread.detach();


	
	}

void MainFrame::SetMainFolder(wxCommandEvent& evt) {

	ddlg = new wxDirDialog(mainPanel, "Escolha a pasta", "C:\\Users\\User");
	if (ddlg->ShowModal() == wxID_CANCEL) {
		return;
	}

	SetFolderPath(ddlg->GetPath());

}