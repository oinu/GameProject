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
		Load();
	}
	~Ranking()
	{

	}
	Score& GetScoreByIndex(int i)
	{
		return ranking[i];
	}

	bool IsTopTen(int num)
	{
		
		bool trobat = false;
		int i = 0;
		while (i < 10 && !trobat)
		{
			if (num > ranking[i].punts)
			{
				trobat = true;
			}
			else
			{
				i++;
			}
		}
		return trobat;
	}

	void AddInTop(int num,const char*name)
	{
		Score tmp;
		Score user(num, name);
		for (int i = 0; i < 10; i++)
		{
			if (user.punts >=ranking[i].punts)
			{
				tmp = ranking[i];
				ranking[i] = user;
				user = tmp;
			}
		}
	}

	void Load()
	{
		ranking = file.ReadRankingAtFile();
	}

	void Save()
	{
		file.WriteRankingAtFile(ranking);
	}

	void Show()
	{
		for (int i = 0; i < 10; i++)
		{
			cout << ranking[i].punts;
			cout << ranking[i].nom << endl;
		}
	}
};