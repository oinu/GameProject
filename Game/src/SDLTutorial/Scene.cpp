#include "Scene.h"


//Constructor per defecte.
Scene::Scene()
{
}

//Constructor amb parametres, que son punters
// a SDL_Renderer, SDL_Texture,GameStat i Difficult
Scene::Scene(Renderer* renderer,GameState *g, Difficulty* d)
{
	r = renderer;
	gameState = g;
	difficult = d;
}


//Destuctors
Scene::~Scene()
{
	r = nullptr;
	gameState = nullptr;
	difficult = nullptr;

	delete r;
	delete gameState;
	delete difficult;
}

//Metode que hereten els fill i estan
// obligats a sobrescriure.
void Scene::Loop()
{
}

//Metode que hereten els fills, per pintar.
//s'ha de sobreescriure.
void Scene::Draw()
{
}
