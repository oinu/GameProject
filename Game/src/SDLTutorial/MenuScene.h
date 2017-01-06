#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
	void Draw();
public:
	MenuScene(SDL_Renderer *, SDL_Texture *,GameState*, Difficulty*);
	~MenuScene();
	void Loop();
};

