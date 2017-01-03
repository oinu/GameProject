#pragma once
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

struct Score
{
public:
	int punts;
	char nom[10];
	Score()
	{

	};
	Score(int p, char* c)
	{
		punts = p;
		for (int i = 0; i < 10; i++)
		{
			nom[i] = c[i];
		}
	}
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
	void WriteRankingAtFile(Score* ranking)
	{
		Score*r = ranking;
		ofstream file("../../res/files/ranking.dat", ios::out |ios::binary);
		for (int i = 0; i < 10; i++)
		{
			file.write(reinterpret_cast<char*>(&r[i].punts), sizeof(r[i].punts));
			file.write(reinterpret_cast<char*>(&r[i].nom), sizeof(r[i].nom));
		}
		file.close();
	}

	//Llegeix el document del ranking i 
	//Retorna un punter al ranking
	Score* ReadRankingAtFile()
	{
		//Prova d'obrir el document
		Score *ran = new Score[10];
		ifstream file("../../res/files/ranking.dat", ios::out | ios::binary);
		if (file.is_open())
		{
			for (int i = 0; i < 10; i++)
			{
				file.read(reinterpret_cast<char*>(&ran[i].punts), sizeof(ran[i].punts));
				file.read(reinterpret_cast<char*>(&ran[i].nom), sizeof(ran[i].nom));
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				ran[i] = { 0,"NONE" };
			}
			WriteRankingAtFile(ran);
		}
		file.close();
		return ran;
	}
};
