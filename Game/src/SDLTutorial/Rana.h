#pragma once
#include "Object.h"
class Rana : public Object
{
private:
	int vidas;
	int puntuacion;
public:
	//CONSTRUCTORS
	Rana();
	Rana(int, int, Rect&, int);
	Rana(int, int, int, int, int, int, int);
	Rana(Rana&);
	~Rana();
};

