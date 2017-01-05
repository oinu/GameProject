#include "GameManager.h"


//Inicialitza tots els valors
GameManager::GameManager()
{
	try {
		//INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		const Uint8 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) &imgFlags)) throw IMG_GetError();

		//WINDOW
		window = SDL_CreateWindow("FROGGER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

		//RENDERER
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)throw SDL_GetError();

		//SPRITES
		globalTexture = IMG_LoadTexture(renderer, "../../res/gfx/frogger_spritesheet.png");
		if (globalTexture == nullptr)throw IMG_GetError();

		//Player
		SDL_Rect froggImg = { 10,360,25,25 };
		player.SetImgBox(froggImg);
		player.PosInicial();

		//Game State
		gameState = GameState::MENU;
		//difficult = Difficulty::EASE;

		//Recuperar el ranking
		ranking = new Ranking(fileManager);

		menu = new MenuScene(renderer, globalTexture,&gameState,&difficult);
		game = new GameScene(renderer, globalTexture, &gameState, &player, &difficult,&fileManager);
		diff = new DifficultyScene(renderer, globalTexture, &gameState, &difficult);
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
}

GameManager::~GameManager()
{
	SDL_DestroyTexture(globalTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GameManager::MainMenu()
{
	menu->Loop();
}

void GameManager::SelectDifficulty()
{
	diff->Loop();
}

void GameManager::Game()
{
	game->Start();
	game->Loop();
}

//Es el gameloop
//Tambe mou el personatge
void GameManager::GameLoop()
{
	while (gameState!=GameState::QUIT)
	{
		if (gameState == GameState::GAME)Game();
		else if (gameState == GameState::MENU)MainMenu();
		else if (gameState == GameState::DIFFICULTY)SelectDifficulty();
	}
	SDL_Quit();
}