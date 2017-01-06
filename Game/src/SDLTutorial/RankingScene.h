#pragma once
#include "Scene.h"
#include "Ranking.h"
#include "Rana.h"
#include "FileManager.h"
class RankingScene :
	public Scene
{
	Ranking *ranking;
	Rana *player;
	bool firstTime;
	void Draw();
	char ObtenirNom(SDL_Keycode);
public:
	RankingScene(SDL_Renderer *, GameState*,Ranking*,Rana*);
	~RankingScene();
	void Loop();
};

