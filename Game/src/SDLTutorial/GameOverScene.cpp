#include "GameOverScene.h"


//Pintem
void GameOverScene::Draw()
{
	//"Netejem el buffer" del renderer.
	r->Clear();

	//Pintem el text Game Over.
	string text = "Game Over";
	SDL_Rect textLocation = { 260,350,250,60 };
	r->DrawText(text.c_str(), textLocation);

	//Renderitzem el buffer.
	r->RenderPresent();

	/*//"Netejem el buffer" del renderer.
	SDL_RenderClear(r);

	//Pintem el text Game Over.
	string text = "Game Over";
	SDL_Rect textLocation = { 260,350,250,60 };
	RenderText(text.c_str(), textLocation);

	//Renderitzem el buffer.
	SDL_RenderPresent(r);	*/
}

//Constructor que te punters com a parametres
// de tipus SDL_Renderer, GameState, Difficulty
GameOverScene::GameOverScene(Renderer * renderer, GameState* g, Difficulty* d)
{
	//Els punters que no fem servir, por que son de
	//la classe pare el apuntem a null.
	r = renderer;
	gameState = g;
	difficult = d;
	
	//Un temps d'espera de 2 segons
	timeWait = 2;
	
	//Inicialitzem les variables.
	currentTime = new time_t();
	timer = new time_t();
}

//Destructor
GameOverScene::~GameOverScene()
{
	delete currentTime;
	delete timer;
}

//Loop de l'escena
void GameOverScene::Loop()
{
	//Guardem el temps actual en el currentTime
	time(currentTime);

	for (bool isRunning = true; isRunning;)
	{
		//Guardem el temps actual en el timer
		time(timer);

		//Obtenim la diferencia de temps entre ells i
		//La guardem a una variable temporal de tipus double.
		double tmp =difftime(*timer,*currentTime);

		//Si la diferencia es superior o igual
		//al temps estipulat.
		if (tmp >= timeWait)
		{
			//Tanquem l'escena i passem al ranking.
			isRunning = false;
			*gameState = GameState::RANKING;
		}
		//Pintem 
		Draw();
	}
}
