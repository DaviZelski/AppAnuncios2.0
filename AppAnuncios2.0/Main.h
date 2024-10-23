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
#include <memory>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <iostream>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS


void TocarAnuncio(Anuncio* anuncio, int loopCount, int musicVolume);

void SetVolumeForProcess(DWORD processID, float volume, int VOLUME_CONTROL);

void FindSpotifyPID(std::vector<DWORD>& spotifyPIDs);