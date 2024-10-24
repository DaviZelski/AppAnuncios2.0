#include "Anuncio.h"
#define _CRT_SECURE_NO_WARNINGS

void Anuncio::SetFilePath(wxString wxFilePath) {
	filePath = string(wxFilePath.mb_str());
}

void Anuncio::setBckgrMusicVol(int mVol) {
	bckgrMusicVol = mVol;
}

void Anuncio::setLoopCount(int SetloopCount) {
	loopCount = SetloopCount;
}


string Anuncio::GetFilePath() {
	return filePath;
}

int Anuncio::getLoopCount() {
	return loopCount;
}

int Anuncio::getBckrMusicVol() {
	return bckgrMusicVol;
}