#include "MainFrame.h"
#include <wx/wx.h>
#include "Anuncio.h"
#include <SFML/Audio.hpp>
#include <string>
#include <shellapi.h>
#include <Windows.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <thread>
#include "Main.h"
#include <memory>
#include <wx/spinctrl.h>
#define _CRT_SECURE_NO_WARNINGS


enum IDs {
	PLAY_BUTTON = 2,
	LOOP_CONTROL = 3
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(PLAY_BUTTON, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE();

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
	
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0x57, 0x65, 0x6b)); // wxColour(0xXX, 0xXX, 0xXX) usar hexadecimal para mudar a cor, vou deixar cinza por enquanto

	//wxMenuBar* menuBar = new wxMenuBar(2, ); https://docs.wxwidgets.org/3.2.5/classwx_menu_bar.html#aebc5627ed35e364d6a9785e22c0dde85

	wxButton* playButton = new wxButton(mainPanel, PLAY_BUTTON, "Tocar Anúncio", wxPoint(100, 100), wxDefaultSize);
	
	wxStaticText* loopControlText = new wxStaticText(mainPanel, wxID_ANY, "Quantidade de loops", wxPoint(220, 80));
	loopControl = new wxSpinCtrl(mainPanel, LOOP_CONTROL, "", wxPoint(250, 100), wxDefaultSize, wxSP_WRAP, 1, 10, 1);

	CreateStatusBar();
	

}


void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	Anuncio* anuncio = new Anuncio;

	/*dlg = new wxDirDialog(mainPanel, "Escolha a pasta", "C:\\Users\\Davi\\Desktop\\avisos");
	dlg->ShowModal();
	dlg->GetPath();*/
	//apenas para selecionar pastas e retornar o caminho, vou deixar aqui pq vai ser util mais tarde

	

	int loopCount = loopControl->GetValue();

	fdlg = new wxFileDialog(mainPanel, "Escolha o anúncio", "C:\\Users\\Davi\\Desktop\\avisos");
	if (fdlg->ShowModal() == wxID_CANCEL) {
		return;  
	}

	wxString fPathConv = wxString::Format("%s", fdlg->GetPath());
	
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

	


	thread anuncioThread(tocarAnuncio, anuncio, loopCount);
	anuncioThread.detach();


	
	}

