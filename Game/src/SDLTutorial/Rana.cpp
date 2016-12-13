#include "Rana.h"



Rana::Rana()
{
	x = 0;
	y = 0;
	vidas = 1;
	puntuacion = 0;
}

Rana::Rana(int aX, int aY, Rect &r, int v)
{
	x = aX;
	y = aY;
	img = r;
	vidas = v;
	puntuacion = 0;
}

Rana::Rana(int aX, int aY, int xImg, int yImg, int width, int heigth, int v)
{
	x = aX;
	y = aY;
	img.SetX(xImg);
	img.SetY(yImg);
	img.SetWidth(width);
	img.SetHeight(heigth);
	vidas = v;
	puntuacion = 0;
}

Rana::Rana(Rana &r)
{
	x = r.x;
	y = r.y;
	img = r.img;
}

Rana::~Rana()
{
}
