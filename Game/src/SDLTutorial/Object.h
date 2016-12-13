#pragma once
#include "Rect.h"

//Se utilizara para los vehiculos, troncos e insectos
class Object
{
protected:
	int x;
	int y;
	Rect img;

public:

	//CONSTRUCTORS
	Object();
	Object(int, int, int, int, int, int);
	Object(int, int, Rect &);
	Object(Object&);
	~Object();

	//FUCTIONS
	int GetX();
	int GetY();
	void SetX(int);
	void SetY(int);

	void Update();
	void Draw();
	Rect BoxCollision();
};

