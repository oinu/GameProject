#pragma once
#include "Scene.h"
#include <vector>
#include "DynamicObject.h"
#include "Rana.h"
#include <iostream>
using namespace std;

class GameScene :
	public Scene
{
	int level;
	Rana *player;
	vector<Object> sceneObject;
	vector<DynamicObject> *riverObjects;
	vector<DynamicObject> *roadObjects;

	bool playerInPlatform;

	bool firstOccupied;
	bool secondOccupied;
	bool thirdOccupied;
	bool fourthOccupied;
	bool fifthOccupied;

	bool Collision(DynamicObject &d, Rana &r);

	void Draw();
	void Update();
public:
	GameScene(SDL_Renderer *, SDL_Texture *, GameState*,int,Rana *);
	~GameScene();
	void Loop();
};

