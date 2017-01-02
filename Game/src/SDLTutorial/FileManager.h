#pragma once
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

struct Score
{
	int punts;
	char* nom;
};
class FileManager
{
	ofstream *writeBinaryFile;
	ifstream *readBinaryFile;

public:
	FileManager()
	{

	}
	~FileManager()
	{
		//Destruim els punter per si de cas.
		delete writeBinaryFile;
		delete readBinaryFile;
	}

	//Escriu en el document
	void WriteRankingAtFile(Score ranking)
	{
		ofstream file("../../res/files/ranking.dat");
		file.write(reinterpret_cast<char*>(&ranking), sizeof(ranking));
		file.close();
	}

	//Llegeix el document del ranking i 
	//Retorna un punter al ranking
	Score& ReadRankingAtFile()
	{
		//Prova d'obrir el document
		Score r;
		ifstream file("../../res/files/ranking.dat");
		file.read(reinterpret_cast<char*>(&r), sizeof(r));
		return r;
	}
};
