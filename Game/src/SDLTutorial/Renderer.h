#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <SDL\SDL_ttf.h>
class Renderer
{
	SDL_Renderer *render;
	SDL_Window *window;
	SDL_Texture* globalTexture;

public:
	Renderer()
	{
		//INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		const Uint8 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) &imgFlags)) throw IMG_GetError();

		//WINDOW
		window = SDL_CreateWindow("FROGGER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

		//RENDERER
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (render == nullptr)throw SDL_GetError();

		//SPRITE
		globalTexture = IMG_LoadTexture(render, "../../res/gfx/frogger_spritesheet.png");
		if (globalTexture == nullptr)throw IMG_GetError();
	}
	~Renderer()
	{
		SDL_DestroyTexture(globalTexture);
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(window);
	}

	void DrawImage(SDL_Rect* collision, SDL_Rect*img)
	{
		SDL_RenderCopy(render, globalTexture, img, collision);
	}

	void RenderPresent()
	{
		SDL_RenderPresent(render);
	}
	void Clear()
	{
		SDL_RenderClear(render);
	}
	void DrawText(const char* s, SDL_Rect rect)
	{
		//Inicialitzem el TTF.
		TTF_Init();

		//Declarem un punter de tipus TTF_Font que contidra
		//la font del fitxer especificat, amb la mida especificada.
		TTF_Font* font = TTF_OpenFont("../../res/fnt/arial.ttf", 20);

		//Declarem la variable foregroundColor que es de tipus SDL_Color
		//i li donem el valor del color Blanc.
		SDL_Color foregroundColor = { 255, 255, 255 };

		//Declarem un punter de tipus SDL_Surface, que conter el text renderitzat
		//amb un color i una font especifiques
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, s, foregroundColor);

		//Declarem una variable del tipus que retorni l'SDL_CreateTextureFromSurface
		//que rep el surface i el renderer.
		auto texture = SDL_CreateTextureFromSurface(render, textSurface);

		//L'introduim dintre el renderer, amb un rectangle en concret.
		SDL_RenderCopy(render, texture, nullptr, &rect);

		//"Allivarem els buffers"
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(texture);

		//Tanquem la font i el TTF.
		TTF_CloseFont(font);
		TTF_Quit();
	}
};