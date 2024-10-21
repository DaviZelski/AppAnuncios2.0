#pragma once
#include <string>
using namespace std;

class Anuncio {
private:
	string filePath = "C:\\Users\\cyber\\source\\repos\\AppAnuncios2.0\\AppAnuncios2.0\\testesAnuncios\\anuncio teste.ogg";
public:
	string GetFilePath() {
		return filePath;
	}
};

