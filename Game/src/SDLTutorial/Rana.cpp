#include "Rana.h"


//Constructor per defecte
Rana::Rana()
{
	img = { 0,0,0,0 };
	collision = { 0,0,0,0 };
	vidas = 1;
	puntuacion = 0;
}

//Constructor amb SDL_Rect i un int com a parametres
Rana::Rana( SDL_Rect &r, SDL_Rect &r2, int v)
{
	img = r;
	collision = r2;
	vidas = v;
	puntuacion = 0;
}

//Constructor amb nombres enters com a parametres
Rana::Rana(int aX, int aY, int xImg, int yImg, int width, int heigth, int v)
{
	collision.x = aX;
	collision.y = aY;
	img.x=xImg;
	img.y=yImg;
	img.w=width;
	img.h=heigth;
	vidas = v;
	puntuacion = 0;
}

//Destructor
Rana::~Rana()
{
	//Es buit ja que no utilitzem punters.
}

//Retorna del nombre de vides.
int Rana::GetVidas()
{
	return vidas;
}

//Retorna la puntuacio del jugador.
int Rana::GetPuntuacion()
{
	return puntuacion;
}

//Li dona el valor v a Vides.
void Rana::SetVidas(int value)
{
	vidas = value;
}

//Li dona el valor v a Puntuacio.
void Rana::SetPuntuacion(int value)
{
	puntuacion = value;
}

//Mou la granota cap amunt.
void Rana::MoveUp()
{
	//Evitem que surti del marge superior y==0
	if(collision.y>0)collision.y -= collision.h;
}

//Mou la granota cap a baix.
//Es passa el HEIGHT per limitar que no surti.
void Rana::MoveDown(int height)
{
	//Evitem que sorti del marge inferiro y==height
	if(collision.y<height-collision.h)collision.y += collision.h;
}

//Mou la granota cap a dreta.
//Es passa el WIDTH per limitar que no surti.
void Rana::MoveRight(int width)
{
	//Evitem que surti del marge dret x==width
	if(collision.x<width-collision.w)collision.x += collision.w;
}

//Mou cap a la esquerra.
void Rana::MoveLeft()
{
	//Evitem que sorti del marge esquerra x==0
	if(collision.x>0)collision.x -= collision.w;
}

//Resta una vida al jugador.
void Rana::RestaVida()
{
	vidas --;
}

//Suma el valor a la puntuacio del jugador.
void Rana::SumaPuntuacion(int value)
{
	puntuacion += value;
}

//Torna a la granota el punt de partida
void Rana::PosInicial()
{
	collision = { 800 / 2 - 50,600 - 100,50,50 };
}
