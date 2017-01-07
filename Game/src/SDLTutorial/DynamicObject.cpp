#include "DynamicObject.h"

//Constructor per defecte buit
DynamicObject::DynamicObject()
{
}

//Constructor amb valors enters i booleans
DynamicObject::DynamicObject(int xPos, int yPos, int width, int height, int xImage, int yImage, int widthImage, int heightImage,bool direction)
{
	reves = direction;
	collision = { xPos,yPos,width,height };
	img = { xImage,yImage,widthImage,heightImage };
	v = 1;
}

//Constructor amb valors SDL_Rect& i la booleana
DynamicObject::DynamicObject(SDL_Rect &i, SDL_Rect &c, bool direction)
{
	collision = c;
	img = i;
	reves = direction;
	v = 1;
}

//Destructor
DynamicObject::~DynamicObject()
{
	//Es buit ja que no te cap punter
	//I no es necessari borrar res.
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

//Retorna la distancia que volem deixar
int DynamicObject::GetDistance()
{
	return distance;
}

//Li dona valor a la distancia
void DynamicObject::SetDistance(int value)
{
	distance = value;
}

//Dona valor a la direccio
void DynamicObject::SetDirection(bool v)
{
	reves = v;
}

//Dona valor a la velocitat
void DynamicObject::SetVelocity(int num)
{
	if (num == 0)v = 1;
	else v = num;
}

//Actualitza la posicio de l'objecte
void DynamicObject::Update(DynamicObject* obj)
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
			int ultim = obj->collision.x + collision.w;

			if(ultim<800)collision.x = 800 + collision.w+distance;
			else collision.x = (ultim + distance);

			obj = this;
		}
	}
	//Si va de dreta a esquerra
	else
	{
		//Comprovem si ha sortit, el col·loquem el principi,
		//fora de la pantalla
		if(collision.x>=800)
		{
			int ultim = obj->collision.x;
			if(ultim>0)collision.x =0-collision.w-distance;
			else collision.x = ultim - distance - collision.w;
			obj = this;
		}
		//Si no ha sortit de la pantalla, el movem
		else
		{
			collision.x += v;
		}
	}
}

//Actualitzem la velocitat segons la puntuacio
//Amb la formula donada en el document.
void DynamicObject::UpdateVelocity(int score)
{
	v += score / 1000;
}
