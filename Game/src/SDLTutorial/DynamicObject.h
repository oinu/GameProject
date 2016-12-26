#pragma once
#include "Object.h"

typedef enum TYPE{PLATFORM, ENEMY};
class DynamicObject :
	public Object
{
private:
	TYPE type;
	bool reves;
	int v;
public:
	DynamicObject();
	DynamicObject(int, int, int, int, int, int,int, int,bool,TYPE);
	DynamicObject(SDL_Rect&, SDL_Rect&, bool,TYPE);
	~DynamicObject();
	
	TYPE GetType();
	bool GetDirection();
	int GetVelociti();
	void SetDirection(bool);
	void SetVelociti(int);
	void SetType(TYPE);
	void Move();
	void Update();
	void Draw();
};

