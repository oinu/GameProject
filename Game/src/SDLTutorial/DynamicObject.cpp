#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(int xPos, int yPos, int width, int height, int xImage, int yImage, int widthImage, int heightImage,bool direction)
{
	reves = direction;
	collision = { xPos,yPos,width,height };
	img = { xImage,yImage,widthImage,heightImage };
	v = 1;
}

DynamicObject::DynamicObject(SDL_Rect &i, SDL_Rect &c, bool direction)
{
	collision = c;
	img = i;
	reves = direction;
	v = 1;
}


DynamicObject::~DynamicObject()
{
}

//Retorna la direccio
bool DynamicObject::GetDirection()
{
	return reves;
}

//Retorna la velocitat
int DynamicObject::GetVelociti()
{
	return v;
}

//Dona valor a la direccio
void DynamicObject::SetDirection(bool v)
{
	reves = v;
}

//Dona valor a la velocitat
void DynamicObject::SetVelociti(int num)
{
	if (num == 0)v = 1;
	else v = num;
}

//Actualitza la posicio de l'objecte
void DynamicObject::Update()
{
	//Si va d'esquerrra a dreta
	if (reves)
	{
		//Comprovem que no ha sortit de la pantalla
		//I el movem
		if(collision.x+collision.w>=0)collision.x -= v;

		//Si ha sortit, el col·loquem el principi,
		//fora de la pantalla
		else
		{
			collision.x += 800 + collision.w;
		}
	}
	//Si va de dreta a esquerra
	else
	{
		//Comprovem si ha sortit, el col·loquem el principi,
		//fora de la pantalla
		if(collision.x>=800)
		{
			collision.x -=800+collision.w;
		}
		//Si no ha sortit de la pantalla, el movem
		else
		{
			collision.x += v;
		}
	}
}

//Pina l'objecte
void DynamicObject::Draw()
{
}
