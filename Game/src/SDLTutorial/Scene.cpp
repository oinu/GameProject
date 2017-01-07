#include "Scene.h"


//Constructor per defecte.
Scene::Scene()
{
}

//Constructor amb parametres, que son punters
// a SDL_Renderer, SDL_Texture,GameStat i Difficult
Scene::Scene(SDL_Renderer * renderer, SDL_Texture *texture,GameState *g, Difficulty* d)
{
	r = renderer;
	t = texture;
	gameState = g;
	difficult = d;
}


//Destuctors
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

//Metode que hereten els fills per pintar text.
void Scene::RenderText(const char* s, SDL_Rect rect)
{
	//Inicialitzem el TTF.
	TTF_Init();

	//Declarem un punter de tipus TTF_Font que contidra
	//la font del fitxer especificat, amb la mida especificada.
	TTF_Font* font = TTF_OpenFont("../../res/fnt/arial.ttf",20);

	//Declarem la variable foregroundColor que es de tipus SDL_Color
	//i li donem el valor del color Blanc.
	SDL_Color foregroundColor = { 255, 255, 255 };

	//Declarem un punter de tipus SDL_Surface, que conter el text renderitzat
	//amb un color i una font especifiques
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, s,foregroundColor);

	//Declarem una variable del tipus que retorni l'SDL_CreateTextureFromSurface
	//que rep el surface i el renderer.
	auto texture = SDL_CreateTextureFromSurface(r, textSurface);
	
	//L'introduim dintre el renderer, amb un rectangle en concret.
	SDL_RenderCopy(r, texture, nullptr, &rect);

	//"Allivarem els buffers"
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);

	//Tanquem la font i el TTF.
	TTF_CloseFont(font);
	TTF_Quit();


}
