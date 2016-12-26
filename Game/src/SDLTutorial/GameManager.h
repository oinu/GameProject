#pragma once
#include "Utilities.h"

#define WIDTH 800 
#define HEIGTH 600

class GameManager
{
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	Rana player;
	SDL_Rect *froggRect;
	SDL_Texture* globalTexture;
	vector<Object> sceneObject;
	vector<DynamicObject> *riverObjects;
	vector<DynamicObject> *roadObjects;
	bool playerInPlatform;
	void SceneInit();
	void DynamicsInit();
	bool Collision(DynamicObject &d, Rana &r);

public:
	GameManager();
	~GameManager();
	void GameLoop();
	void Update();
	void Draw();
};

