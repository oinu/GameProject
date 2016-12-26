#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

//S'ha de fer be, aixo no xuta!!!!!
#define R Renderer::Instance()

class Renderer
{
private:
	SDL_Renderer *renderer;
	Renderer()
	{
	}

public:

	inline static Renderer &Instance(void) {
		static Renderer renderer;
		return renderer;
	}

	~Renderer()
	{

	}

};