#pragma once
#include "Object.h"
class Rana : public Object
{
private:
	//guarda les vides del jugador
	int vidas;

	//guarda la puntuació del jugador
	int puntuacion;
public:
	//CONSTRUCTORS
	Rana();
	Rana(SDL_Rect&, SDL_Rect &, int);
	Rana(int, int, int, int, int, int, int);
	~Rana();

	//FUNCTIONS

	//Retorna del nombre de vides.
	int GetVidas();

	//Retorna la puntuacio del jugador.
	int GetPuntuacion();

	//Li dona el valor v a Vides.
	void SetVidas(int);

	//Li dona el valor v a Puntuacio.
	void SetPuntuacion(int);

	//Mou la granota cap amunt.
	void MoveUp();

	//Mou la granota cap a baix.
	//Es passa el HEIGHT per limitar que no surti.
	void MoveDown(int);

	//Mou la granota cap a dreta.
	//Es passa el WIDTH per limitar que no surti.
	void MoveRight(int);

	//Mou cap a la esquerra.
	void MoveLeft();

	//Resta una vida al jugador.
	void RestaVida();

	//Suma el valor a la puntuacio del jugador.
	void SumaPuntuacion(int);

	void PosInicial();
};

