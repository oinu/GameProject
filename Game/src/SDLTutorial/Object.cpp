#include "Object.h"



Object::Object()
{
	img = { 0,0,0,0 };
	collision = { 0,0,0,0 };
}

Object::Object(int aX, int aY, int xImage, int yImage, int aWidth, int aHeight)
{
	collision.x = aX;
	collision.y = aY;
	img = { xImage,yImage,aWidth,aHeight };
}

Object::Object( SDL_Rect & aImg, SDL_Rect &aCollision)
{
	img = aImg;
	collision = aCollision;
}

Object::~Object()
{
}

int Object::GetX()
{
	return collision.x;
}

int Object::GetY()
{
	return collision.y;
}

SDL_Rect & Object::GetImgBox()
{
	return img;
}

SDL_Rect & Object::GetCollision()
{
	return collision;
}

void Object::SetX(int value)
{
	collision.x = value;
}

void Object::SetY(int value)
{
	collision.y = value;
}

void Object::SetImgBox(SDL_Rect &value)
{
	img = value;
}

void Object::SetCollision(SDL_Rect &value)
{
	collision = value;
}

void Object::Update()
{
}

void Object::Draw()
{
}
