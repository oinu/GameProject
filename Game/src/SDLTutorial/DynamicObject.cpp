#include "DynamicObject.h"
#include <iostream>

using namespace std;

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(int xPos, int yPos, int width, int height, int xImage, int yImage, int widthImage, int heightImage,bool direction,TYPE tp)
{
	reves = direction;
	collision = { xPos,yPos,width,height };
	img = { xImage,yImage,widthImage,heightImage };
	v = 1;
	type = tp;
}

DynamicObject::DynamicObject(SDL_Rect &i, SDL_Rect &c, bool direction,TYPE tp)
{
	collision = c;
	img = i;
	reves = direction;
	v = 1;
	type = tp;
}


DynamicObject::~DynamicObject()
{
}

TYPE DynamicObject::GetType()
{
	return type;
}

bool DynamicObject::GetDirection()
{
	return reves;
}

int DynamicObject::GetVelociti()
{
	return v;
}

void DynamicObject::SetDirection(bool v)
{
	reves = v;
}

void DynamicObject::SetVelociti(int num)
{
	if (num == 0)v = 1;
	else v = num;
}

void DynamicObject::SetType(TYPE value)
{
	type = value;
}

void DynamicObject::Move()
{
	collision.x = collision.x + 50;
}

void DynamicObject::Update()
{
	if (reves)
	{
		if(collision.x+collision.w>=0)collision.x -= v;
		else
		{
			collision.x += 800 + collision.w;
		}
	}
	else
	{
		if(collision.x>=800)
		{
			collision.x -=800+collision.w;
		}
		else
		{
			collision.x += v;
		}
	}
}

void DynamicObject::Draw()
{
}
