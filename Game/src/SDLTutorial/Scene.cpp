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
	r = nullptr;
	t = nullptr;
	gameState = nullptr;
	difficult = nullptr;

	delete r;
	delete t;
	delete gameState;
	delete difficult;
}

void Scene::Loop()
{
}

void Scene::Draw()
{
}

void Scene::RenderText(const char* s, SDL_Rect rect)
{
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("../../res/fnt/arial.ttf",20);
	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Color backgroundColor = { 0, 0, 255 };

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, s,foregroundColor);	
	auto texture = SDL_CreateTextureFromSurface(r, textSurface);
	
	SDL_RenderCopy(r, texture, nullptr, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	TTF_Quit();


}
