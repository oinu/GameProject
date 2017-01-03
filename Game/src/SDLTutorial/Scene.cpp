#include "Scene.h"



Scene::Scene()
{
}

Scene::Scene(SDL_Renderer * renderer, SDL_Texture *texture,GameState *g)
{
	r = renderer;
	t = texture;
	gameState = g;
}


Scene::~Scene()
{
}

/*void Scene::Loop(GameState &g)
{
	gameState = g;
	for (bool isRunning = true; isRunning;)
	{
		isRunning=Update(false);
		Draw();
	}
}*/

void Scene::Loop()
{
}

void Scene::Draw()
{
}
