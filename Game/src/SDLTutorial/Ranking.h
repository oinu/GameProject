#pragma once
#include "FileManager.h"

class Ranking
{
	//Punter de l'array score
	Score *ranking;

	//Declaracio variable per acces a fitxer.
	FileManager file;

public:

	//Constructor que passa el fitxer com a referencia
	Ranking(FileManager &f)
	{
		file = f;

		//Una vagada tenim el fitxer,
		//Carraguem el ranking 
		Load();
	}

	//Destructor
	~Ranking()
	{
		delete[] ranking;
	}

	//Retorna l'Score d'una posicio en concret
	Score& GetScoreByIndex(int i)
	{
		return ranking[i];
	}

	//Retorna si la puntuacio es dins al ranking
	bool IsTopTen(int num)
	{
		//booleana per saber si l'hem trobat
		bool trobat = false;

		//Declarem una variable entera
		int i = 0;

		//Mentre sigui inferior a 10
		//O no l'hem trobat
		while (i < 10 && !trobat)
		{
			//Si el num es mes gran que una posicio
			//del ranking, es top10
			if (num > ranking[i].punts)
			{
				//Indiquem que l'hem trobat per sortir
				//Del bucle
				trobat = true;
			}
			//Sino, passem a l'altre element.
			else
			{
				i++;
			}
		}
		//Retorna el si s'ha trobat o no.
		return trobat;
	}


	//Afageix al ranking, passantli un nom i una puntuacio
	void AddInTop(int num,const char*name)
	{
		//Necessitem una variable temporal per fer corre
		// els elements del ranking
		Score tmp;

		//Creem l'Score del jugador.
		Score user(num, name);

		//Recorrem els 10 elements
		for (int i = 0; i < 10; i++)
		{
			//Quant troba que el de l'usuari es mes gran
			//que el que hi ha al ranking.
			if (user.punts >=ranking[i].punts)
			{
				//passem el ranking a tmp.
				tmp = ranking[i];

				//donem el valor de user a ranking[i].
				ranking[i] = user;

				//I li donem el valor de tmp a user,
				//Aixi els ferem corre tots.
				user = tmp;
			}
		}
	}

	//Carrega el ranking.
	void Load()
	{
		ranking = file.ReadRankingAtFile();
	}

	//Guarda el ranking.
	void Save()
	{
		file.WriteRankingAtFile(ranking);
	}

	//Mostra el ranking
	//DESFASSAT!!!
	void Show()
	{
		for (int i = 0; i < 10; i++)
		{
			cout << ranking[i].punts;
			cout << ranking[i].nom << endl;
		}
	}
};