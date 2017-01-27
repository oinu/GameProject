#pragma once
#include "Scene.h"
class DifficultyScene :
	public Scene
{
	//Pinta l'escena
	void Draw();
public:
	//Constructor que te com a parametres punters
	//De tipus SDL_Renderer, SDL_Texture, GameState i Difficulty
	DifficultyScene(Renderer *, GameState*, Difficulty*);
	
	//Destructor
	~DifficultyScene();

	//Loop de l'escena
	void Loop();
};

