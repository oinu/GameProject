#pragma once
#include "Scene.h"
#include <time.h>
class GameOverScene :
	public Scene
{
	//Punter tipus time_t que conter el temps de l'escena.
	time_t *currentTime;

	//Punter tipus time_t que conter el temps actual.
	time_t* timer;

	//Declaracio de la variable timeWait, que conte el temps a esperar.
	int timeWait;

	//Pintem
	void Draw();
public:

	//Constructor que te punters com a parametres
	// de tipus SDL_Renderer, GameState, Difficulty
	GameOverScene(Renderer *, GameState*, Difficulty*);

	//Destuctor
	~GameOverScene();

	//Loop de l'escena.
	void Loop();
};

