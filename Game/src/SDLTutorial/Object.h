#pragma once
#include <SDL\SDL.h>

//Se utilizara para los vehiculos, troncos e insectos
class Object
{
protected:
	SDL_Rect img;
	SDL_Rect collision;

public:

	//CONSTRUCTORS
	Object();
	Object(int, int, int, int, int, int);
	Object( SDL_Rect &, SDL_Rect&);
	~Object();

	//FUCTIONS
	int GetX();
	int GetY();
	SDL_Rect& GetImgBox();
	SDL_Rect& GetCollision();
	void SetX(int);
	void SetY(int);
	void SetImgBox(SDL_Rect&);
	void SetCollision(SDL_Rect&);

	void Update();
	void Draw();
};

