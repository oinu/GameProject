#pragma once
#include "FileManager.h"

class Ranking
{
	Score *ranking;
	FileManager file;
public:

	Ranking(FileManager &f)
	{
		file = f;
		f.WriteRankingAtFile({ 1,"caca" });
		Score i = f.ReadRankingAtFile();
		cout << i.nom;
	}
	~Ranking()
	{

	}
	Score& GetRankingByIndex(int i)
	{
		return Score();
	}
};