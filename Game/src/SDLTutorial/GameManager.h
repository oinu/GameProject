#pragma once
#include "Utilities.h"

#define WIDTH 800 
#define HEIGTH 600

class GameManager
{
private:
	MenuScene *menu;
	DifficultyScene *diff;
	GameScene *game;
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

	FileManager fileManager;

	Ranking *ranking;

public:

	//CONSTRUCTORS

	//Inicialitza tots els valors
	GameManager();
	~GameManager();
	
	//FUNCIONS

	//Menu Principal
	void MainMenu();

	void SelectDifficulty();

	//Jugar
	void Game();

	//Es el gameloop
	//Tambe mou el personatge
	void GameLoop();
};

