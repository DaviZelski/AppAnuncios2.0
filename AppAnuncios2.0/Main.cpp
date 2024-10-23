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
#define _CRT_SECURE_NO_WARNINGS

void tocarAnuncio(Anuncio* anuncio, int loopCount) {
    sf::Music announcementPlayer;

    if (!announcementPlayer.openFromFile(anuncio->GetFilePath())) {
        wxLogStatus("caminho nao encontrado");
        return;
    }

    for (int i = 0; i < loopCount; i++) {
        announcementPlayer.play();

        // Aguarda enquanto a música está tocando
        while (announcementPlayer.getStatus() == sf::Music::Playing) {
            sf::sleep(sf::milliseconds(100));
        }
    }
}