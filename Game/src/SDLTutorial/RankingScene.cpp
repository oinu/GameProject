#include "RankingScene.h"



void RankingScene::Draw()
{
	SDL_RenderClear(r);

	string text;
	SDL_Rect textLocation;
	for (int i = 0; i < 10; i++)
	{
		text = to_string(i + 1);
		text += ".- ";
		text += ranking->GetScoreByIndex(i).nom;
		text += "  ";
		text += to_string(ranking->GetScoreByIndex(i).punts);
		textLocation = { 260,10+(50*i),250,40 };
		RenderText(text.c_str(), textLocation);
	}

	text = "Press ENTER to continue";
	textLocation = { 230,530,280,40 };
	RenderText(text.c_str(), textLocation);
	SDL_RenderPresent(r);
}

char RankingScene::ObtenirNom(SDL_Keycode k)
{
	string c = "";
	int a = 0;
	char caca = ' ';
	c = to_string(k);
	a = stoi(c);
	caca = a;
	return caca;
}

RankingScene::RankingScene(SDL_Renderer * renderer, GameState* g, Ranking* ran,Rana *p)
{
	r = renderer;
	t = nullptr;
	gameState = g;
	difficult = nullptr;
	ranking = ran;
	player = p;
	firstTime = true;
}


RankingScene::~RankingScene()
{
}

void RankingScene::Loop()
{
	for (bool isRunning = true; isRunning;)
	{
		if (ranking->IsTopTen(player->GetPuntuacion()) && firstTime && player->GetPuntuacion()>0)
		{
			string name="";
			cout << "Escriu un nom (maxim 10 caracters)" << endl;
			cin >> name;
			ranking->AddInTop(player->GetPuntuacion(), name.c_str());
			ranking->Save();
			firstTime = false;
		}
		else
		{
			SDL_Event evnt;
			while (SDL_PollEvent(&evnt))
			{
				switch (evnt.type)
				{
				case SDL_KEYDOWN:
					if (evnt.key.keysym.sym == SDLK_RETURN)
					{
						isRunning = false;
						*gameState = GameState::MENU;
					}
					break;
				}
			}
			Draw();
		}
	}
}
