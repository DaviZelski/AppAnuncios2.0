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
#define _CRT_SECURE_NO_WARNINGS


void tocarAnuncio(Anuncio* anuncio, int loopCount);
