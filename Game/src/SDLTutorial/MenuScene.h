#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
	//Pinta 
	void Draw();
public:
	//CONSTRUCTORS

	//Constructor amb parametres, que son punters
	//SDL_Renderer,SDL_Texture,GameState,Difficulty.
	MenuScene(Renderer *,GameState*, Difficulty*);

	//Destructor
	~MenuScene();

	//Loop de l'escena
	void Loop();
};

