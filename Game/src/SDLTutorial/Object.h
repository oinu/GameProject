#pragma once
#include <SDL\SDL.h>

//Se utilizara para los vehiculos, troncos e insectos
class Object
{
protected:
	//Rectangle referent a la imatge
	SDL_Rect img;

	//Rectangle referent a la pantalla
	SDL_Rect collision;

public:

	//CONSTRUCTORS

	//Constructor per defecte
	Object();

	//Constructor amb enters com a parametres
	Object(int, int, int, int, int, int);

	//Constructor amb SDL_Rect com a parametres
	Object( SDL_Rect &, SDL_Rect&);

	//Destuctor
	~Object();

	//FUCTIONS

	//Retorna el valor de X
	int GetX();

	//Retorna el valor de Y
	int GetY();

	//Retorna el valor de img
	SDL_Rect& GetImgBox();

	//Retorna el valor de collision
	SDL_Rect& GetCollision();

	//Dona valor a collision.x
	void SetX(int);

	//Dona valor a collision.y
	void SetY(int);

	//Dona valor a img
	void SetImgBox(SDL_Rect&);

	//Dona valor a collision
	void SetCollision(SDL_Rect&);

	// Actualitza els objectes
	void Update();

	//Pinta els objectes
	void Draw(SDL_Renderer*, SDL_Texture*);
};

