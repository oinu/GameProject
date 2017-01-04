#pragma once
#include "Scene.h"
#include <vector>
#include "DynamicObject.h"
#include "Rana.h"
#include <iostream>
#include <time.h>
using namespace std;

class GameScene :
	public Scene
{
	int level;
	Rana *player;
	Object insect;
	bool insectTake;
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
	bool Collision(Object &d, Rana &r);

	void Draw();
	void Update();
	void InsertInsect();
public:
	GameScene(SDL_Renderer *, SDL_Texture *, GameState*,Rana *,Difficulty*);
	~GameScene();
	void Loop();
	void Start();
};

