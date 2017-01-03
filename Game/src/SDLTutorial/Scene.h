#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
typedef enum GameState { MENU, GAME, QUIT, RANKING };
class Scene
{
protected:
	SDL_Renderer *r;
	SDL_Texture *t;
	GameState *gameState;
	virtual void Draw();
public:
	Scene();
	Scene(SDL_Renderer *, SDL_Texture *,GameState*);
	~Scene();
	virtual void Loop();
};

