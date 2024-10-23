#pragma once
#include <string>
#include <wx/wx.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Anuncio {
private:
	string filePath; //"C:\\Users\\Davi\\Desktop\\avisos\\fim do expediente.wav";
public:
	int SetFilePath(wxString wxFilePath) {
		filePath = string(wxFilePath.mb_str());  
		return 0;
	}

	string GetFilePath() {
		return filePath;
	}
};

