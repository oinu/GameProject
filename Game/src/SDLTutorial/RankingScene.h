#pragma once
#include "Scene.h"
#include "Ranking.h"
#include "Rana.h"
#include "FileManager.h"
class RankingScene :
	public Scene
{
	//Declaracio del punter ranking de tipus Ranking
	Ranking *ranking;

	//Declaracio del punter player de tipus Rana
	Rana *player;

	//Declaracio de la variable firsTime de tipus bool
	bool firstTime;

	//Pinta
	void Draw();

	//Retorne el caracter de la tecla apretada
	//Actualment no esta en us
	char ObtenirNom(SDL_Keycode);

public:
	//CONSTRUCTORS

	//Constructor amb parametres pointer
	//SDL_Renderer, GameState, Ranking, Rana
	RankingScene(SDL_Renderer *, GameState*,Ranking*,Rana*);

	//Destructor
	~RankingScene();

	//Loop de l'escena
	void Loop();
};

