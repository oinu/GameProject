#include "Object.h"



Object::Object()
{
	x = 0;
	y = 0;
}

Object::Object(int aX, int aY, int xImage, int yImage, int aWidth, int aHeight)
{
	x = aX;
	y = aY;
	img.SetX(xImage);
	img.SetY(yImage);
	img.SetWidth(aWidth);
	img.SetHeight(aHeight);
}

Object::Object(int aX, int aY, Rect & aImg)
{
	x = aX;
	y = aY;
	img = aImg;
}

Object::Object(Object &obj)
{
	x = obj.x;
	y = obj.y;
	img = obj.img;
}

Object::~Object()
{
}

int Object::GetX()
{
	return x;
}

int Object::GetY()
{
	return y;
}

void Object::SetX(int value)
{
	x = value;
}

void Object::SetY(int value)
{
	y = value;
}

void Object::Update()
{
}

void Object::Draw()
{
}

Rect Object::BoxCollision()
{
	return img;
}
