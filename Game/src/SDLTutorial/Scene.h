#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <SDL\SDL_ttf.h>
#include "Enumerators.h"
#include <iostream>
using namespace std;
class Scene
{
protected:
	SDL_Renderer *r;
	SDL_Texture *t;
	GameState *gameState;
	Difficulty *difficult;
	virtual void Draw();
	void RenderText(const char* s,SDL_Rect);
public:
	Scene();
	Scene(SDL_Renderer *, SDL_Texture *,GameState*, Difficulty*);
	~Scene();
	virtual void Loop();
};

