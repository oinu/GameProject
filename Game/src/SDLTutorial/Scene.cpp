#include "Scene.h"



Scene::Scene()
{
}

Scene::Scene(SDL_Renderer * renderer, SDL_Texture *texture,GameState *g, Difficulty* d)
{
	r = renderer;
	t = texture;
	gameState = g;
	difficult = d;
}


Scene::~Scene()
{
}

void Scene::Loop()
{
}

void Scene::Draw()
{
}
