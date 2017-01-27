#include "GameManager.h"


//Inicialitza tots els valors
GameManager::GameManager()
{
	try {

		//Player
		SDL_Rect froggImg = { 10,360,25,25 };
		player.SetImgBox(froggImg);
		player.PosInicial();

		//Game State
		gameState = GameState::MENU;

		//Recuperar el ranking
		ranking = new Ranking(fileManager);

		//Inicialitzem els punters
		menu = new MenuScene(&renderer,&gameState,&difficult);
		game = new GameScene(&renderer, &gameState, &player, &difficult,&fileManager);
		diff = new DifficultyScene(&renderer, &gameState, &difficult);
		gameOver= new GameOverScene(&renderer, &gameState, &difficult);
		rank = new RankingScene(&renderer, &gameState, ranking,&player);
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
}

//Destroy
GameManager::~GameManager()
{	
}

//Menu Principal
void GameManager::MainMenu()
{
	//Crida la funcio loop del menu
	menu->Loop();
}

//Seleccio de dificultat
void GameManager::SelectDifficulty()
{
	//Crida la funcio loop del menu dificultat
	diff->Loop();
}

//Jugar
void GameManager::Game()
{
	//Inicialitza els valors del joc
	game->Start();

	//Comença a jugar
	game->Loop();
}

//Es el gameloop
//Tambe mou el personatge
void GameManager::GameLoop()
{
	//Mentre no volguem marxar del joc
	while (gameState!=GameState::QUIT)
	{
		if (gameState == GameState::GAME)Game();
		else if (gameState == GameState::MENU)MainMenu();
		else if (gameState == GameState::DIFFICULTY)SelectDifficulty();
		else if (gameState == GameState::GAMEOVER)gameOver->Loop();
		else if (gameState == GameState::RANKING)rank->Loop();
	}
	SDL_Quit();
}