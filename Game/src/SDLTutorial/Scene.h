#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <SDL\SDL_ttf.h>
#include "Enumerators.h"
#include <iostream>
using namespace std;
class Scene
{
	//Indiquem que es protected perque
	//els fills puguin accedir els atributs.
protected:

	//Declaracio del punter r, que contindra el renderer
	SDL_Renderer *r;

	//Declaracio del punter t, que contidra la textura
	SDL_Texture *t;

	//Declaracio del punter gameState, que contindra
	//l'estat del joc.
	GameState *gameState;

	//Declaracio del punter difficult, que contidra
	//la dificultat del joc.
	Difficulty *difficult;

	//Metode que hereten els fills, per pintar.
	//s'ha de sobreescriure.
	virtual void Draw();

	//Metode que hereten els fills per pintar text.
	void RenderText(const char* s,SDL_Rect);

public:
	//CONSTRUCTORS

	//Constructor per defecte.
	Scene();

	//Constructor amb parametres, que son punters
	// a SDL_Renderer, SDL_Texture,GameStat i Difficulty
	Scene(SDL_Renderer *, SDL_Texture *,GameState*, Difficulty*);

	//Destuctors
	~Scene();

	//Metode que hereten els fill i estan
	// obligats a sobrescriure.
	virtual void Loop();
};

