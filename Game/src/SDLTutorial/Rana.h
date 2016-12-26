#pragma once
#include "Object.h"
class Rana : public Object
{
private:
	int vidas;
	int puntuacion;
public:
	//CONSTRUCTORS
	Rana();
	Rana(SDL_Rect&, SDL_Rect &, int);
	Rana(int, int, int, int, int, int, int);
	~Rana();
	int GetVidas();
	int GetPuntuacion();
	void SetVidas(int);
	void SetPuntuacion(int);
	void MoveUp();
	void MoveDown(int);
	void MoveRight(int);
	void MoveLeft();
	void RestaVida();
	void SumaPuntuacion(int);
};

