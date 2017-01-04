#pragma once
#include "Scene.h"
class DifficultyScene :
	public Scene
{
	SDL_Texture * menu;
	void Draw();
public:
	DifficultyScene(SDL_Renderer *, SDL_Texture *, GameState*, Difficulty*);
	~DifficultyScene();
	void Loop();
};

