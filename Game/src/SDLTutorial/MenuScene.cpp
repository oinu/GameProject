#include "MenuScene.h"



MenuScene::MenuScene(SDL_Renderer * renderer, SDL_Texture *global, GameState* g, Difficulty* d)
{
	r = renderer;
	t = global;
	gameState = g;
	menu= IMG_LoadTexture(r, "../../res/gfx/options.png");
	difficult = d;
}

MenuScene::~MenuScene()
{
	r = nullptr;
	t = nullptr;
	gameState = nullptr;
	
	delete t;
	delete r;
	delete gameState;
}

void MenuScene::Loop()
{
	SDL_Event evnt;
	for (bool isRunning = true; isRunning;)
	{
		//INPUT HANDLER
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				isRunning = false;
				*gameState = GameState::QUIT;
				break;
			case SDL_MOUSEBUTTONDOWN:

				if (evnt.button.y >= 210 && evnt.button.y <= 270
					&& (evnt.button.x >= 300 && evnt.button.x <= 470))
				{
					isRunning = false;
					*gameState = GameState::GAME;
				}
				else if (evnt.button.y >= 350 && evnt.button.y <= 410
					&& evnt.button.x >= 260 && evnt.button.x <= 510)
				{
					//cout << "Ranking" << endl;
				}
				else if (evnt.button.y >= 510 && evnt.button.y <= 570
					&& evnt.button.x >= 320 && evnt.button.x <= 450)
				{
					isRunning = false;
					*gameState = GameState::QUIT;
				}
				break;
			case SDL_KEYDOWN:

				if (evnt.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
					*gameState = GameState::QUIT;
				}
				break;
			}

		}
		Draw();
	}
}

void MenuScene::Draw()
{
	SDL_RenderClear(r);
	SDL_RenderCopy(r, t, new SDL_Rect{ 0,0,800,50 }, new SDL_Rect{ 0,0,800,100 });
	SDL_RenderCopy(r, menu, new SDL_Rect{ 0,0,640,480 }, new SDL_Rect{ 0,100,800,600 });

	SDL_RenderPresent(r);
}
