#include "Rana.h"



Rana::Rana()
{
	img = { 0,0,0,0 };
	collision = { 0,0,0,0 };
	vidas = 1;
	puntuacion = 0;
}

Rana::Rana( SDL_Rect &r, SDL_Rect &r2, int v)
{
	img = r;
	collision = r2;
	vidas = v;
	puntuacion = 0;
}

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

Rana::~Rana()
{
}

int Rana::GetVidas()
{
	return vidas;
}

int Rana::GetPuntuacion()
{
	return puntuacion;
}

void Rana::SetVidas(int value)
{
	vidas = value;
}

void Rana::SetPuntuacion(int value)
{
	puntuacion = value;
}

void Rana::MoveUp()
{
	if(collision.y>0)collision.y -= collision.h;
}

void Rana::MoveDown(int height)
{
	if(collision.y<height-collision.h)collision.y += collision.h;
}

void Rana::MoveRight(int width)
{
	if(collision.x<width-collision.w)collision.x += collision.w;
}

void Rana::MoveLeft()
{
	if(collision.x>0)collision.x -= collision.w;
}

void Rana::RestaVida()
{
	vidas --;
}

void Rana::SumaPuntuacion(int value)
{
	puntuacion += value;
}
