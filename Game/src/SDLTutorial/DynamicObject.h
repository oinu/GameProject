#pragma once
#include "Object.h"

class DynamicObject :
	public Object
{
private:
	//Indica el centit true= esquerra a dreta
	bool reves;

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

	//Dona valor a la direccio
	void SetDirection(bool);

	//Dona valor a la velocitat
	void SetVelociti(int);

	//Actualitza la posicio de l'objecte
	void Update();
};

