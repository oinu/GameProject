#pragma once
#include "Object.h"

class DynamicObject :
	public Object
{
private:
	//Indica el centit true= esquerra a dreta
	bool reves;

	//Indica la distancia entre l'objecte i el seguent
	int distance;

	//Indica la velocitat de moviment dels objectes
	int v;
public:
	//CONSTRUCTORS

	//Constructor per defecte buit
	DynamicObject();

	//Constructor amb valors enters i booleans
	DynamicObject(int, int, int, int, int, int,int, int,bool);

	//Constructor amb valors SDL_Rect& i la booleana
	DynamicObject(SDL_Rect&, SDL_Rect&, bool);

	//Destructor
	~DynamicObject();
	
	//FUNCTIONS

	//Retorna la direccio
	bool GetDirection();

	//Retorna la velocitat
	int GetVelociti();

	//Retorna la distancia que volem deixar
	int GetDistance();

	//Li dona valor a la distancia
	void SetDistance(int);

	//Dona valor a la direccio
	void SetDirection(bool);

	//Dona valor a la velocitat
	void SetVelocity(int);

	//Actualitza la posicio de l'objecte
	void Update(DynamicObject*);

	//Actualitzem la velocitat segons la puntuacio
	//Amb la formula donada en el document.
	void UpdateVelocity(int);
};

