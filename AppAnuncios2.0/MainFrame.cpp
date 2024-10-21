#include "MainFrame.h"
#include <wx/wx.h>
#include "Anuncio.h"
#include <SFML/Audio.hpp>

enum IDs {
	PLAY_BUTTON = 2
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(PLAY_BUTTON, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE();

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* mainPanel = new wxPanel(this);

	wxButton* playButton = new wxButton(mainPanel, PLAY_BUTTON, "Tocar An�ncio", wxDefaultPosition, wxDefaultSize);

	CreateStatusBar();

}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	Anuncio* anuncio = new Anuncio;
	sf::SoundBuffer buffer;

	wxString string = wxString::Format("%s", anuncio->GetFilePath());
	wxLogStatus(string);
}