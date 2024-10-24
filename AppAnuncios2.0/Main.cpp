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
#include <Psapi.h>
#include <vector>

#include "Main.h"
#include "MainFrame.h"
#include "Anuncio.h"
#define _CRT_SECURE_NO_WARNINGS


#define  VOLUME_UP  1
#define  VOLUME_DOWN  2

//
//void MainLogicLoop() {
//    
//}



void TocarAnuncio(Anuncio* anuncio) {

    std::vector<DWORD> spotifyPIDs;
    FindSpotifyPID(spotifyPIDs);

    for (DWORD spotifyPID : spotifyPIDs) {
        SetVolumeForProcess(spotifyPID, (anuncio->getBckrMusicVol()), VOLUME_DOWN);
    }
    
    sf::Music announcementPlayer;

    if (!announcementPlayer.openFromFile(anuncio->GetFilePath())) {

        wxString string = wxString::Format("Caminho nao encontrado");
        wxLogStatus(string);
        return;

    }
    else {
        wxString string = wxString::Format("Tocando %s, com a musica no volume %d", anuncio->GetFilePath(), anuncio->getBckrMusicVol());
        wxLogStatus(string);
    }


    for (int i = 0; i < (anuncio->getLoopCount()); i++) {
        announcementPlayer.play();

        while (announcementPlayer.getStatus() == sf::Music::Playing) {
            sf::sleep(sf::milliseconds(100));
        }
    }

    for (DWORD spotifyPID : spotifyPIDs) {
        SetVolumeForProcess(spotifyPID, 100, VOLUME_UP);
    }
}


void FindSpotifyPID(std::vector<DWORD>& spotifyPIDs) {
    
    DWORD* pidBuffer = nullptr;
    DWORD bytesReturned = 0;
    DWORD bufferSize = 1024;

    bool enumSuccess = false;

    while (!enumSuccess) {
        
        delete[] pidBuffer;

        pidBuffer = new DWORD[bufferSize];

        if (EnumProcesses(pidBuffer, sizeof(DWORD) * bufferSize, &bytesReturned)) {
            if (bytesReturned < sizeof(DWORD) * bufferSize) {
                enumSuccess = true;
            }
            else {
                bufferSize *= 2;
            }
        }
        else {
            wxLogStatus("Falha ao enumerar processos!");
            delete[] pidBuffer;
            return;
        }
    }

    for (DWORD i = 0; i < bufferSize; i++) {
        DWORD pid = pidBuffer[i];
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

        if (hProcess != NULL) {
            TCHAR lpBaseName[MAX_PATH];

            if (GetModuleBaseName(hProcess, NULL, lpBaseName, sizeof(lpBaseName) / sizeof(TCHAR))) {
                
                if (_tcscmp(lpBaseName, _T("Spotify.exe")) == 0) {
                    spotifyPIDs.push_back(pid);
                }
            }

            CloseHandle(hProcess);

        }
    }
    delete[] pidBuffer;
}

void SetVolumeForProcess(DWORD processID, float musicVolume, int VOLUME_CONTROL) {
    CoInitialize(nullptr);

    IMMDeviceEnumerator* deviceEnumerator = nullptr;
    IMMDevice* device = nullptr;
    IAudioSessionManager2* sessionManager = nullptr;
    IAudioSessionEnumerator* sessionEnumerator = nullptr;

    CoCreateInstance(_uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, _uuidof(IMMDeviceEnumerator), (void**)&deviceEnumerator);

    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);

    device->Activate(_uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr, (void**)&sessionManager);

    sessionManager->GetSessionEnumerator(&sessionEnumerator);

    int sessionCount = 0;
    sessionEnumerator->GetCount(&sessionCount);

    for (int i = 0; i < sessionCount; i++) {
        IAudioSessionControl* sessionControl = nullptr;
        sessionEnumerator->GetSession(i, &sessionControl);

        IAudioSessionControl2* sessionControl2 = nullptr;
        sessionControl->QueryInterface(_uuidof(IAudioSessionControl2), (void**)&sessionControl2);

        DWORD pid = 0;
        sessionControl2->GetProcessId(&pid);

        if (pid == processID) {
            ISimpleAudioVolume* audioVolume = nullptr;
            sessionControl2->QueryInterface(_uuidof(ISimpleAudioVolume), (void**)&audioVolume);


            float currentVolume;
            audioVolume->GetMasterVolume(&currentVolume);
            
            if (VOLUME_CONTROL == VOLUME_DOWN) {
                
                for (float i = currentVolume; i > (musicVolume/100.0f); i -= 0.01) {
                    audioVolume->SetMasterVolume(i, nullptr);
                    Sleep(8);
                }
            }
            else {
                
                for (float i = currentVolume; i <= (musicVolume / 100.0f); i += 0.01) {
                    audioVolume->SetMasterVolume(i, nullptr);
                    Sleep(8);
                }
            }
            
            audioVolume->Release();
            audioVolume = nullptr;
        }
    }
}