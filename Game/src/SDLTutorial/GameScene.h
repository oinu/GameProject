#pragma once
#include "Scene.h"
#include <vector>
#include "DynamicObject.h"
#include "Rana.h"
#include <time.h>
#include "FileManager.h"

class GameScene :
	public Scene
{
	//Declaracio variable int que contindra el nivell actual.
	int level;

	//Declaracio del punter que contindra el file Manager.
	FileManager *fileManager;

	//Declaracio del punter que contidra el player.
	Rana *player;

	//Declaracio de la variable que contindra
	//la puntuacio que cada vagada arribi/passi dels 1000 punts
	int oldPuntuation;

	//Declaracio de la variable que contidra,
	//si s'ha d'incrementar la velocitat dels objectes.
	bool incrementVelocity;

	//Declaracio de la variable que conte l'insecte.
	Object insect;

	//Declaracio de la variable que contidra si
	//no es mostra per pantalla o si.
	bool insectTake;

	//Declaracio de la variable que contindra si
	//Esta preparat per apareixa a l'escenari o no.
	bool insectPopUp;

	//Declaracio de la variable que contindra el temps
	//inicial del jugador.
	int initalTime;

	//Declaracio de la variable que contindra el temps
	//actula que li queda el jugador.
	int playerTime;

	//Declaracio del punter de tipus time_t,
	//que contindra el temps guardat del jugador.
	time_t* playerTimeSaved;

	//Declaracio del punter de tipus time_t
	//que contindra el temps actual del jugador.
	time_t* playerCurrentTime;

	//Declaracio del punter de tipus time_t
	//que contindra el temps guardat de l'insecte.
	time_t* insectTimeSaved;

	//Declaracio del punter de tipus time_t
	//que contindra el temps actual de l'insecte.
	time_t* insectCurrentTime;

	//Vector de tipus Object, on guardem
	//els objectes inmovils del joc parets i riu.
	vector<Object> sceneObject;

	//Array de vectors de tipus DynamicObject
	//que conter les files i els elements de les files,
	//que correseponen al riu.
	vector<DynamicObject> *riverLinesObjects;

	//Punter de punters de tipus DynamicObject,
	//per saber quin son els ultims elements de cada fila.
	//Del riu.
	DynamicObject **lastRiverObject;

	//Declaracio de la variable que contidra,
	//el nombre d'elements per fila, del riu.
	int riverElementsForLine;

	//Array de vectors de tipus DynamicObject
	//que conter les files i els elements de les files,
	//que correseponen a la carretera.
	vector<DynamicObject> *roadLinesObjects;

	//Punter de punters de tipus DynamicObject,
	//per saber quin son els ultims elements de cada fila.
	//De la carretera
	DynamicObject **lastRoadObject;

	//Declaracio de la variable que contidra,
	//el nombre d'elements per fila, de la carretera.
	int roadElementsForLine;

	//Declaracio de la booleana, per saber si el
	//player es troba dins una plataforma.
	bool playerInPlatform;

	//Declaracio de les variables booleanes, per saber
	//quina de les caselles finals estan ocupades.
	bool firstOccupied;
	bool secondOccupied;
	bool thirdOccupied;
	bool fourthOccupied;
	bool fifthOccupied;

	//FUNCTION

	//Retorna si hi ha hagut colisio entre la granota
	// i algun element de tipus DynamicObject.
	//Troncs i cotxes.
	bool Collision(DynamicObject &d, Rana &r);

	//Sobrescrivim el metode Collision, amb la finalitat
	//de tambe saber si colisiona amb Objects,
	//com l'insecte.
	bool Collision(Object &d, Rana &r);

	//Pintem mentre juguem
	void Draw();

	//Pintem el menu pausa
	void DrawPause();

	//Actualitzem els valors i comprovem colisions.
	//accepcio del jugador.
	void Update();

	//Coloquem l'insecte dins l'escenari.
	void InsertInsect();

	//Li treiem temps de vida al jugador.
	void DecreaseTime();

public:
	//CONSTRUCTORS

	//Constructor amb parametres, que son punters de tipus,
	//SDL_Renderer,SDL_Texture,GameState,Rana,Difficulty i FilManager
	GameScene(SDL_Renderer *, SDL_Texture *, GameState*,Rana *,Difficulty*,FileManager*);

	//Destructor
	~GameScene();

	//Loop de l'escena.
	void Loop();

	//Inicialitzar variables
	void Start();
};

