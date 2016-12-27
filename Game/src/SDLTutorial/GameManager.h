#pragma once
#include "Utilities.h"

#define WIDTH 800 
#define HEIGTH 600

typedef enum GameState { MENU, GAME,QUIT };

class GameManager
{
private:

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

	//L'escenari
	vector<Object> sceneObject;

	//Objectes del riu que es mouen
	//Troncs,etc.
	vector<DynamicObject> *riverObjects;

	//Objectes de la carretera que es mouen
	//Cotxes,etc.
	vector<DynamicObject> *roadObjects;

	//Si el jugador esta sobre una plataforma
	//Tronc, etc
	bool playerInPlatform;

	//Determina si les caselles finals estan ocupades
	bool firstOccupied;
	bool secondOccupied;
	bool thirdOccupied;
	bool fourthOccupied;
	bool fifthOccupied;

	//FUNCIONS PRIVADES

	//Inicialitza els objectes de l'escenari
	void SceneInit();

	//Inicialitza tots els objectes dinamics
	//Troncs,cotxes,etc.
	void DynamicsInit();

	//Detecta la col·lisio entre
	//el personatge i l'objecte dinamic.
	bool Collision(DynamicObject &d, Rana &r);

public:

	//CONSTRUCTORS

	//Inicialitza tots els valors
	GameManager();
	~GameManager();
	
	//FUNCIONS

	//Menu Principal
	void MainMenu();

	//Jugar
	void Game();

	//Es el gameloop
	//Tambe mou el personatge
	void GameLoop();

	//Actualitza tots els elements del joc
	//Menys quant es mou el personatge
	void Update();

	//Pinta els objectes
	void Draw();
};

