#pragma once
#include "Utilities.h"

//Definim el width i el height de la finestre
#define WIDTH 800 
#define HEIGTH 600

class GameManager
{
private:
	
	//Punter que conter el Menu Principal
	MenuScene *menu;

	//Punter que conter el menu Dificultat
	DifficultyScene *diff;

	//Punter que conter el joc.
	GameScene *game;

	//Punter que conter el menu GamerOver
	GameOverScene *gameOver;

	//Punter que conter el menu Ranking
	RankingScene *rank;

	//Determina la dificultat.
	Difficulty difficult;

	//Determina en quin moment del joc ens trobem
	GameState gameState;
	//Punter que conter la informacio de la finestra
	SDL_Window *window;

	//Punter que conter el renderer
	SDL_Renderer *renderer;

	//Jugador
	Rana player;

	//La textura on es troba totes les imatges
	SDL_Texture* globalTexture;

	//Variable que conter el FileManager
	FileManager fileManager;

	//Punter que conte el ranking
	Ranking *ranking;

public:

	//CONSTRUCTORS

	//Constructor per defecte
	GameManager();

	//Destructor
	~GameManager();
	
	//FUNCIONS

	//Menu Principal
	void MainMenu();

	//Seleccio de dificultat
	void SelectDifficulty();

	//Jugar
	void Game();

	//Es el gameloop
	//Tambe mou el personatge
	void GameLoop();
};

