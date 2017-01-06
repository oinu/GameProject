#pragma once
#include "Scene.h"
class DifficultyScene :
	public Scene
{
	void Draw();
public:
	DifficultyScene(SDL_Renderer *, SDL_Texture *, GameState*, Difficulty*);
	~DifficultyScene();
	void Loop();
};

