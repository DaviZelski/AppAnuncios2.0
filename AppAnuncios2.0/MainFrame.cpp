#include "MainFrame.h"
#include <wx/wx.h>
#include "Anuncio.h"
#include <SFML/Audio.hpp>
#include <string>
using namespace std;

enum IDs {
	PLAY_BUTTON = 2
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(PLAY_BUTTON, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE();

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* mainPanel = new wxPanel(this);

	wxButton* playButton = new wxButton(mainPanel, PLAY_BUTTON, "Tocar Anúncio", wxDefaultPosition, wxDefaultSize);

	CreateStatusBar();



}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	Anuncio* anuncio = new Anuncio;
	sf::Music music;
	if (!music.openFromFile(anuncio->GetFilePath())){
		//nao carrega pqp vai a merda
		
		wxLogStatus("Caminho nao encontrado");
	}
}