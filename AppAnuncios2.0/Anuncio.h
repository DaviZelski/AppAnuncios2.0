#pragma once
#include <string>
using namespace std;

class Anuncio {
private:
	string filePath = "C:\\Users\\cyber\\source\\repos\\AppAnuncios2.0\\x64\\Debug\\anuncioTeste.ogg";
public:
	string GetFilePath() {
		return filePath;
	}
};

