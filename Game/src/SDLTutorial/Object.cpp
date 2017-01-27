#include "Object.h"


//Constructor per defecte
Object::Object()
{
	img = { 0,0,0,0 };
	collision = { 0,0,0,0 };
}

//Constructor amb enters com a parametres
Object::Object(int aX, int aY, int xImage, int yImage, int aWidth, int aHeight)
{
	collision.x = aX;
	collision.y = aY;
	img = { xImage,yImage,aWidth,aHeight };
}

//Constructor amb SDL_Rect com a parametres
Object::Object( SDL_Rect & aImg, SDL_Rect &aCollision)
{
	img = aImg;
	collision = aCollision;
}

//Destuctor
Object::~Object()
{
	//No destruim res, ja que no em utilitzat cap punter
}

//Retorna el valor de X
int Object::GetX()
{
	return collision.x;
}

//Retorna el valor de Y 
int Object::GetY()
{
	return collision.y;
}

//Retorna el valor de img
SDL_Rect & Object::GetImgBox()
{
	return img;
}

//Retorna el valor de collision
SDL_Rect & Object::GetCollision()
{
	return collision;
}

//Dona valor a collision.x
void Object::SetX(int value)
{
	collision.x = value;
}

//Dona valor a collision.y
void Object::SetY(int value)
{
	collision.y = value;
}

//Dona valor a img
void Object::SetImgBox(SDL_Rect &value)
{
	img = value;
}

//Dona valor a collision
void Object::SetCollision(SDL_Rect &value)
{
	collision = value;
}

// Actualitza els objectes
void Object::Update()
{
}

//Pinta els objectes
void Object::Draw(Renderer* r)
{
	//SDL_RenderCopy(r, t, &img, &collision);
	r->DrawImage(&collision, &img);
}
