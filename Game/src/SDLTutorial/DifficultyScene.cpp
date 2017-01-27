#include "DifficultyScene.h"


//Constructor que te com a parametres punters
//De tipus SDL_Renderer, SDL_Texture, GameState i Difficulty
DifficultyScene::DifficultyScene(Renderer * renderer, GameState* g, Difficulty* d)
{
	//Els passem com a punteres amb la finalitat
	//de poder modificar el contingut des d'aquesta classe
	r = renderer;
	gameState = g;
	difficult = d;
}

//Destructor
DifficultyScene::~DifficultyScene()
{
	gameState = nullptr;
	delete r;
	delete gameState;
}

//Loop de l'escena
void DifficultyScene::Loop()
{
	//Revem un event
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
				//Si ha fet clic a la creueta de la finestra
			case SDL_QUIT:
				//Indiquem que volem sortir
				isRunning = false;
				*gameState = GameState::QUIT;
				break;
				//Si ha fet clic amb el mouse
			case SDL_MOUSEBUTTONDOWN:
				
				//Si la fet sobre la zona del Ease
				if (evnt.button.y >= 210 && evnt.button.y <= 270
					&& (evnt.button.x >= 300 && evnt.button.x <= 470))
				{
					//Indiquem que volem sortir del bucle
					isRunning = false;
					//Li indiquem el valor de la dificultat
					*difficult = Difficulty::EASE;
					//Canviem l'estat del joc.
					*gameState = GameState::GAME;
				}
				//Si la fet sobre la zona del Medium
				else if (evnt.button.y >= 350 && evnt.button.y <= 410
					&& evnt.button.x >= 260 && evnt.button.x <= 510)
				{
					//Indiquem que volem sortir del bucle.
					isRunning = false;
					//Li indiquem el valor de la dificultat
					*difficult = Difficulty::MEDIUM;
					//Canviem l'estat del joc.
					*gameState = GameState::GAME;
				}
				//Si la fet sobre la zona del Hard
				else if (evnt.button.y >= 510 && evnt.button.y <= 570
					&& evnt.button.x >= 320 && evnt.button.x <= 450)
				{
					//Indiquem que volem sortir del bucle.
					isRunning = false;
					//Li indiquem el valor de la dificultat.
					*difficult = Difficulty::HARD;
					//Canviem l'estat del joc.
					*gameState = GameState::GAME;
				}
				break;
				//Si apreta una tecla.
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

//Pintem
void DifficultyScene::Draw()
{
	//"Neteja el buffer" del render
	r->Clear();

	//Afegeix el titul del frogger.
	r->DrawImage( new SDL_Rect{ 0,0,800,100 }, new SDL_Rect{ 0,0,800,50 });

	//Afegeix el text Easy
	string text = "Easy";
	SDL_Rect textLocation = { 300,210,170,60 };
	r->DrawText(text.c_str(), textLocation);

	//Afegeix el text Medium
	text = "Medium";
	textLocation = { 260,350,250,60 };
	r->DrawText(text.c_str(), textLocation);

	//Afegeix el text Hard
	text = "Hard";
	textLocation = { 320,510,130,60 };
	r->DrawText(text.c_str(), textLocation);

	//Pintem tots elements del renderer
	r->RenderPresent();

	/*//"Neteja el buffer" del render
	SDL_RenderClear(r);

	//Afegeix el titul del frogger.
	SDL_RenderCopy(r, t, new SDL_Rect{ 0,0,800,50 }, new SDL_Rect{ 0,0,800,100 });

	//Afegeix el text Easy
	string text = "Easy";
	SDL_Rect textLocation = { 300,210,170,60 };
	RenderText(text.c_str(), textLocation);

	//Afegeix el text Medium
	text = "Medium";
	textLocation = { 260,350,250,60 };
	RenderText(text.c_str(), textLocation);

	//Afegeix el text Hard
	text = "Hard";
	textLocation = { 320,510,130,60 };
	RenderText(text.c_str(), textLocation);

	//Pintem tots elements del renderer
	SDL_RenderPresent(r);*/
}