#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
typedef enum GameState { MENU, GAME, QUIT, RANKING,GAMEOVER };
typedef enum Difficulty { EASE, MEDIUM, HARD};
class Scene
{
protected:
	SDL_Renderer *r;
	SDL_Texture *t;
	GameState *gameState;
	Difficulty *difficult;
	virtual void Draw();
public:
	Scene();
	Scene(SDL_Renderer *, SDL_Texture *,GameState*, Difficulty*);
	~Scene();
	virtual void Loop();
};

