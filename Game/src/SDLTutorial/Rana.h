#pragma once
#include "Object.h"
class Rana : public Object
{
	//S'HA BARREJAT ELS IDIOMES
	//NO S'HA DE FER
private:
	//guarda les vides del jugador
	int vidas;

	//guarda la puntuació del jugador
	int puntuacion;
public:
	//CONSTRUCTORS

	//Constructor per defecte
	Rana();

	//Constructor amb SDL_Rect i un int com a parametres
	Rana(SDL_Rect&, SDL_Rect &, int);

	//Constructor amb nombres enters com a parametres
	Rana(int, int, int, int, int, int, int);

	//Destructor
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

	//Torna a la granota el punt de partida
	void PosInicial();
};

