#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

int main(int, char*[]) {

	try {

		//INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		const Uint8 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) &imgFlags)) throw IMG_GetError();

		//WINDOW
		SDL_Window * window;
		const int WIDTH = 1024;
		const int HEIGTH = 780;
		window=SDL_CreateWindow("caca", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, SDL_WINDOW_BORDERLESS|SDL_WINDOW_SHOWN);

		//RENDERER
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)throw SDL_GetError();

		//SPRITES
		SDL_Texture* bgTexture=IMG_LoadTexture(renderer, "../../res/gfx/bg.jpg");
		if (bgTexture == nullptr)throw IMG_GetError();
		SDL_Rect bgRect = { 0, 0, WIDTH, HEIGTH };

		SDL_Texture* playerTexture = IMG_LoadTexture(renderer, "../../res/gfx/blue.png");
		if (playerTexture == nullptr)throw IMG_GetError();
		SDL_Rect playerRect = {(WIDTH>>1)-5,(HEIGTH>>1)-50,100,100};
		SDL_Rect playerTarget = { 0,0,100,100 };
		//GAMELOOP
		SDL_Event evnt;
		for (bool isRunning=true;isRunning;)
		{
			//INPUT HANDLER
			while (SDL_PollEvent(&evnt))
			{
				switch (evnt.type)
				{
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_MOUSEMOTION:
					playerTarget.x = evnt.motion.x - 50;
					playerTarget.y = evnt.motion.y - 50;
					break;
				}

			}
			//UPDATE
			playerRect.x += (playerTarget.x - playerRect.x) * 0.1f;
			playerRect.y += (playerTarget.y - playerRect.y) * 0.1f;

			//DRAW
			SDL_RenderCopy(renderer, bgTexture,nullptr,&bgRect);
			SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
			SDL_RenderPresent(renderer);
		}
		SDL_DestroyTexture(playerTexture);
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
	SDL_Quit();
	return 0;
}
