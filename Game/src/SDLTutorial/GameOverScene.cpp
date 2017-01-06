#include "GameOverScene.h"



void GameOverScene::Draw()
{
	SDL_RenderClear(r);

	string text = "Game Over";
	SDL_Rect textLocation = { 260,350,250,60 };
	RenderText(text.c_str(), textLocation);

	SDL_RenderPresent(r);	
}

GameOverScene::GameOverScene(SDL_Renderer * renderer, GameState* g, Difficulty* d)
{
	r = renderer;
	t = nullptr;
	gameState = g;
	difficult = d;
	timeWait = 2;
	currentTime = new time_t();
	timer = new time_t();
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Loop()
{
	time(currentTime);

	for (bool isRunning = true; isRunning;)
	{
		time(timer);
		double tmp =difftime(*timer,*currentTime);
		if (tmp >= timeWait)
		{
			isRunning = false;
			*gameState = GameState::RANKING;
		}
		Draw();
	}
}
