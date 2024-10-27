#pragma once
#include <string>
#include <wx/wx.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Anuncio {
private:
	string filePath;
	int loopCount;
	int bckgrMusicVol;
public:
	void SetFilePath(wxString wxFilePath);

	void setBckgrMusicVol(int mVol);

	void setLoopCount(int SetloopCount);


	string GetFilePath();

	int getLoopCount();

	int getBckrMusicVol();
};