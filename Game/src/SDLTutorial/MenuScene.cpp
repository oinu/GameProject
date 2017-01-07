#include "MenuScene.h"


//Constructor amb parametres, que son punters
//SDL_Renderer,SDL_Texture,GameState,Difficulty.
MenuScene::MenuScene(SDL_Renderer * renderer, SDL_Texture *global, GameState* g, Difficulty* d)
{
	r = renderer;
	t = global;
	gameState = g;
	difficult = d;
}

//Destructor
MenuScene::~MenuScene()
{
	r = nullptr;
	t = nullptr;
	gameState = nullptr;
	
	delete t;
	delete r;
	delete gameState;
}

//Loop de l'escena
void MenuScene::Loop()
{
	//Declara la variable evnt.
	SDL_Event evnt;

	//Mentre ens volguem mantenir dintre l'escena
	for (bool isRunning = true; isRunning;)
	{
		//INPUT HANDLER
		//Agafem l'event del SDL_PollEvent
		while (SDL_PollEvent(&evnt))
		{
			//Mirem de quin tipus es l'event.
			switch (evnt.type)
			{
			case SDL_QUIT:
				//Indiquem que volem sortir
				isRunning = false;
				*gameState = GameState::QUIT;
				break;

				//Si ha fet clic amb el mouse
			case SDL_MOUSEBUTTONDOWN:

				//Si la fet sobre la zona del Start
				if (evnt.button.y >= 210 && evnt.button.y <= 270
					&& (evnt.button.x >= 300 && evnt.button.x <= 470))
				{
					//Indiquem que volem sortir del bucle
					isRunning = false;
					//Canviem l'estat a difficulty.
					*gameState = GameState::DIFFICULTY;
				}

				//Si la fet sobre la zona del Ranking
				else if (evnt.button.y >= 350 && evnt.button.y <= 410
					&& evnt.button.x >= 260 && evnt.button.x <= 510)
				{
					//Indiquem que volem sortir del bucle
					isRunning = false;
					//Canviem l'estat a ranking.
					*gameState = GameState::RANKING;
				}

				//Si la fet sobre la zona del Exit
				else if (evnt.button.y >= 510 && evnt.button.y <= 570
					&& evnt.button.x >= 320 && evnt.button.x <= 450)
				{
					//Indiquem que volem sortir del bucle
					isRunning = false;
					//Canviem l'estat a quit.
					*gameState = GameState::QUIT;
				}
				break;

				//Si a paretat una tecla
			case SDL_KEYDOWN:

				//Mirem quina tecla a apretat
				if (evnt.key.keysym.sym == SDLK_ESCAPE)
				{
					//Indiquem que volem sortir.
					isRunning = false;
					*gameState = GameState::QUIT;
				}
				break;
			}

		}
		//Pintem
		Draw();
	}
}

//Pinta
void MenuScene::Draw()
{
	//"Netejem el renderer"
	SDL_RenderClear(r);

	//Afegim el titul
	SDL_RenderCopy(r, t, new SDL_Rect{ 0,0,800,50 }, new SDL_Rect{ 0,0,800,100 });

	//Declarem la variable text i 
	//l'inicialitzem amb el contingut Start.
	string text = "Start";

	//Declarem la variable textLocation i l'inicialitzem.
	SDL_Rect textLocation = { 300,210,170,60 };

	//L'introduim dintre el renderer.
	RenderText(text.c_str(), textLocation);

	//Donem el valor a la variable text i 
	//l'inicialitzem amb el contingut Ranking.
	text = "Ranking";

	//Donem el valor la variable textLocation i l'inicialitzem.
	textLocation = { 260,350,250,60 };

	//L'introduim dintre el renderer.
	RenderText(text.c_str(), textLocation);

	//Donem el valor a la variable text i 
	//l'inicialitzem amb el contingut Exit.
	text = "Exit";

	//Donem el valor la variable textLocation i l'inicialitzem.
	textLocation = { 320,510,130,60 };

	//L'introduim dintre el renderer.
	RenderText(text.c_str(), textLocation);

	//Pintem tots elements del renderer
	SDL_RenderPresent(r);
}
