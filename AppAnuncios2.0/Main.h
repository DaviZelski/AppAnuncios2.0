#include <wx/wx.h>
#include <SFML/Audio.hpp>
#include <string>
#include <shellapi.h>
#include <Windows.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <thread>
#include <memory>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <iostream>
#include <vector>

#include "MainFrame.h"
#include "Anuncio.h"
#define _CRT_SECURE_NO_WARNINGS


//void MainLogicLoop();

void TocarAnuncio(Anuncio* anuncio);

void SetVolumeForProcess(DWORD processID, float volume, int VOLUME_CONTROL);

void FindSpotifyPID(std::vector<DWORD>& spotifyPIDs);