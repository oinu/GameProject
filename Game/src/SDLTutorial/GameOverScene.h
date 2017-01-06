#pragma once
#include "Scene.h"
#include <time.h>
class GameOverScene :
	public Scene
{
	time_t *currentTime;
	time_t* timer;
	int timeWait;
	void Draw();
public:
	GameOverScene(SDL_Renderer *, GameState*, Difficulty*);
	~GameOverScene();
	void Loop();
};

