#pragma once
#include "Object.h"

class DynamicObject :
	public Object
{
private:
	//Indica el centit true= esquerra a dreta
	bool reves;
	int distance;

	//Indica la velocitat de moviment dels objectes
	int v;
public:
	//CONSTRUCTORS
	DynamicObject();
	DynamicObject(int, int, int, int, int, int,int, int,bool);
	DynamicObject(SDL_Rect&, SDL_Rect&, bool);
	~DynamicObject();
	
	//FUNCTIONS

	//Retorna la direccio
	bool GetDirection();

	//Retorna la velocitat
	int GetVelociti();

	int GetDistance();

	void SetDistance(int);

	//Dona valor a la direccio
	void SetDirection(bool);

	//Dona valor a la velocitat
	void SetVelocity(int);

	//Actualitza la posicio de l'objecte
	void Update(DynamicObject*);

	void UpdateVelocity(int);
};

