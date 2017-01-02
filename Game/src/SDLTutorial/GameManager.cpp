#include "GameManager.h"


//Inicialitza els objectes de l'escenari
void GameManager::SceneInit()
{
	// Paret verda
	SDL_Rect forestCollision = { 0,0,WIDTH,80 };
	SDL_Rect forestImg = { 0,60,WIDTH,60 };
	Object forest(forestImg, forestCollision);
	sceneObject.push_back(forest);

	//Riu
	SDL_Rect waterCollision = { 0,70,WIDTH,150 };
	SDL_Rect waterImg = { 0,120,WIDTH,35 };
	Object water(waterImg, waterCollision);
	sceneObject.push_back(water);
}

//Inicialitza tots els objectes dinamics
//Troncs,cotxes,etc.
void GameManager::DynamicsInit()
{
	//River Objects

	//Array de 3 elemetns, ja que son 3 files
	riverObjects = new vector<DynamicObject>[3];

	SDL_Rect woodCollision;
	SDL_Rect woodImg = { 7,165,180,25 };
	DynamicObject wood(woodImg, woodCollision, false);
	int finalX = WIDTH - WIDTH / 3;

	/*woodCollision = { 0,70,WIDTH / 3,50 };
	wood.SetCollision(woodCollision);
	wood.SetImgBox(woodImg);
	wood.SetDirection(false);
	riverObjects[2].push_back(wood);

	woodCollision = { WIDTH - woodCollision.w,120,WIDTH / 3,50 };
	woodImg = { 7,165,180,25 };
	wood.SetCollision(woodCollision);
	wood.SetImgBox(woodImg);
	wood.SetDirection(true);
	riverObjects[1].push_back(wood);

	woodCollision = { 0,170,WIDTH / 3,50 };
	woodImg = { 7,165,180,25 };
	wood.SetCollision(woodCollision);
	wood.SetImgBox(woodImg);
	wood.SetDirection(false);
	riverObjects[0].push_back(wood);*/

	for (int i=0; i < 3; i++)
	{
		woodCollision = { 0 -(woodCollision.w*i +100*i),70,WIDTH / 3,50 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(false);
		riverObjects[2].push_back(wood);

		woodCollision = { finalX + (woodCollision.w*i +100*i),120,WIDTH / 3,50 };
		woodImg = { 7,165,180,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(true);
		riverObjects[1].push_back(wood);

		woodCollision = { 0 - (woodCollision.w*i + 100 * i),170,WIDTH / 3,50 };
		woodImg = { 7,165,180,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(false);
		riverObjects[0].push_back(wood);
	}

	// Road Objects

	//Array de 3 elemetns, ja que son 3 files
	roadObjects = new vector<DynamicObject>[3];
	finalX = WIDTH - 75;
	
	SDL_Rect carCollision = { 0,300,75,50 };
	SDL_Rect carImg = { 40,265,35,25 };
	DynamicObject car(carImg, carCollision, false);

	for (int i = 0; i < 3; i++)
	{
		carCollision = { 0-(carCollision.w*i + 100 * i),300,75,50 };
		carImg = { 40,265,35,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(false);
		roadObjects[2].push_back(car);

		carCollision = { finalX + (carCollision.w*i + 100 * i),350,75,50 };
		carImg = { 80,265,35,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(true);
		roadObjects[1].push_back(car);

		carCollision = { 0 - (carCollision.w*i + 100 * i),400,75,50 };
		carImg = { 40,265,35,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(false);
		roadObjects[0].push_back(car);
	}

}

//Detecta la col·lisio entre
//el personatge i l'objecte dinamic.
bool GameManager::Collision(DynamicObject & d, Rana & r)
{	

	//Despres de ferla 5 vagades, es queda aixi
	//La colisio es des del punt centric de la r

	//Calculem el punt centric de la r
	int rXCenter = r.GetCollision().x + r.GetCollision().w / 2;
	int rYCenter = r.GetCollision().y + r.GetCollision().h / 2;

	//Calculem els 4 punts de la d
	int dYMax = d.GetCollision().y + d.GetCollision().h;
	int dXMax = d.GetCollision().x + d.GetCollision().w;
	int dXMin = d.GetCollision().x;
	int dYMin = d.GetCollision().y;

	//Mirem si hi ha collisio
	bool collVertical = dYMin<=rYCenter && dYMax>= rYCenter;
	bool collLateral = dXMin<=rXCenter && dXMax>=rXCenter;

	if (collLateral  && collVertical)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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
		menuTexture = IMG_LoadTexture(renderer, "../../res/gfx/options.png");
		if (globalTexture == nullptr)throw IMG_GetError();

		//Player
		SDL_Rect froggCollision = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
		SDL_Rect froggImg = { 10,360,25,25 };
		player.SetImgBox(froggImg);
		player.SetCollision(froggCollision);
		player.SetVidas(10);

		//Scene
		SceneInit();

		//Dynamic Objects
		DynamicsInit();

		firstOccupied = false;
		secondOccupied = false;
		thirdOccupied = false;
		fourthOccupied = false;
		fifthOccupied = false;

		//Game State
		gameState = GameState::MENU;
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
	delete[]riverObjects;
	delete[]roadObjects;
}

void GameManager::MainMenu()
{
	SDL_Event evnt;
	for (bool isRunning = true; isRunning;)
	{
		//INPUT HANDLER
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				isRunning = false;
				gameState = GameState::QUIT;
				break;
			case SDL_MOUSEBUTTONDOWN:

				if (evnt.button.y >= 210 && evnt.button.y <= 270
					&& (evnt.button.x >= 300 && evnt.button.x <= 470))
				{
					isRunning = false;
					gameState = GameState::GAME;
				}
				else if (evnt.button.y >= 350 && evnt.button.y <= 410
					&& evnt.button.x >= 260 && evnt.button.x <= 510)
				{
					cout << "Ranking" << endl;
				}
				else if (evnt.button.y >= 510 && evnt.button.y <= 570
					&& evnt.button.x >= 320 && evnt.button.x <= 450)
				{
					isRunning = false;
					gameState = GameState::QUIT;
				}
				break;
			case SDL_KEYDOWN:

				if (evnt.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
					gameState = GameState::QUIT;
				}
				break;
			}

		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, globalTexture, new SDL_Rect{ 0,0,800,50 }, new SDL_Rect{0,0,WIDTH,100});
		SDL_RenderCopy(renderer, menuTexture, new SDL_Rect{ 0,0,640,480 }, new SDL_Rect{ 0,100,WIDTH,HEIGTH });
		
		SDL_RenderPresent(renderer);
	}
}

void GameManager::Game()
{
	try {
		SDL_Event evnt;
		for (bool isRunning = true; isRunning;)
		{
			//INPUT HANDLER
			while (SDL_PollEvent(&evnt))
			{
				switch (evnt.type)
				{
				case SDL_QUIT:
					isRunning = false;
					gameState = GameState::QUIT;
					break;
				case SDL_KEYDOWN:
					SDL_Keycode key = evnt.key.keysym.sym;

					switch (key)
					{
					case SDLK_ESCAPE:
						isRunning = false;
						gameState = GameState::QUIT;
						break;

						//Arrows
					case SDLK_UP:

						//Si esta a l'ultim tronc
						if (player.GetCollision().y == 50)
						{
							//Comprova si les caselles estan disponibles
							if (!firstOccupied && player.GetCollision().x >= 20 && player.GetCollision().x <= 55)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								firstOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!secondOccupied && player.GetCollision().x >= 173 && player.GetCollision().x <= 225)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								secondOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!thirdOccupied && player.GetCollision().x >= 350 && player.GetCollision().x <= 400)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								thirdOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!fourthOccupied && player.GetCollision().x >= 520 && player.GetCollision().x <= 565)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								fourthOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!fifthOccupied && player.GetCollision().x >= 700 && player.GetCollision().x <= 735)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								fifthOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}

						}
						//Si no es a l'ultim tronc, abansa normal
						else player.MoveUp();
						break;
					case SDLK_DOWN:
						player.MoveDown(HEIGTH);
						break;
					case SDLK_LEFT:
						player.MoveLeft();
						break;
					case SDLK_RIGHT:
						player.MoveRight(WIDTH);
						break;

						// WSAD
					case SDLK_w:
						//Si esta a l'ultim tronc
						if (player.GetCollision().y == 50)
						{
							//Comprova si les caselles estan disponibles
							if (!firstOccupied && player.GetCollision().x >= 20 && player.GetCollision().x <= 55)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								firstOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!secondOccupied && player.GetCollision().x >= 173 && player.GetCollision().x <= 225)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								secondOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!thirdOccupied && player.GetCollision().x >= 350 && player.GetCollision().x <= 400)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								thirdOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!fourthOccupied && player.GetCollision().x >= 520 && player.GetCollision().x <= 565)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								fourthOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}
							else if (!fifthOccupied && player.GetCollision().x >= 700 && player.GetCollision().x <= 735)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player.MoveUp();
								fifthOccupied = true;
								SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
								player.SetCollision(temp);
							}

						}
						//Si no es a l'ultim tronc, abansa normal
						else player.MoveUp();
						break;
					case SDLK_s:
						player.MoveDown(HEIGTH);
						break;
					case SDLK_a:
						player.MoveLeft();
						break;
					case SDLK_d:
						player.MoveRight(WIDTH);
						break;
					default:
						break;
					}
				}

			}
			//UPDATE
			Update();

			//DRAW
			Draw();
		}
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
	SDL_Quit();
}

//Es el gameloop
//Tambe mou el personatge
void GameManager::GameLoop()
{
	while (gameState!=GameState::QUIT)
	{
		if (gameState == GameState::GAME)Game();
		else if (gameState == GameState::MENU)MainMenu();
	}
}

//Actualitza tots els elements del joc
//Menys quant es mou el personatge
void GameManager::Update()
{
	//Per cada element de la llista
	for (int i = 0; i<3; i++)
	{
		//Recorrem tots el objectes del riu
		for (DynamicObject &obj : riverObjects[i])
		{
			//Els actualitzem
			obj.Update();

			//Comprovem si hi ha colisio o no
			if (Collision(obj, player))
			{
				//En cas afirmatiu
				//diguem que esta sobre una plataforma
				playerInPlatform = true;

				//Si va de dreta a esquerra
				if (!obj.GetDirection() && (player.GetCollision().x + player.GetCollision().w < 800))
				{
					player.SetX(player.GetCollision().x + obj.GetVelociti());
				}

				//Si va d'esquerra a dreta
				else
				{
					if (player.GetCollision().x > 0)
					{
						player.SetX(player.GetCollision().x - obj.GetVelociti());
					}
				}
			}
		}

		//Recorrem tots els objectes de la carretera
		for (DynamicObject &obj : roadObjects[i])
		{
			//Els actualitzem
			obj.Update();

			//Detectem si colisionen
			if (Collision(obj, player))
			{
				//Si colisionen, li restem vida
				//i el coloquem el punt de partida
				player.RestaVida();
				SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
				player.SetCollision(temp);
				cout << player.GetVidas() << endl;
			}
		}
	}

	//Si el jugador és dintre de l'aigua
	//i no esta sobre una plataforma
	if (player.GetCollision().y > 30 && player.GetCollision().y < 200 && !playerInPlatform)
	{
		//Si colisionen, li restem vida
		//i el coloquem el punt de partida
		player.RestaVida();
		SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
		player.SetCollision(temp);
		cout << player.GetVidas() << endl;
	}

	//li donem el valor a false amb la finalitat de que si
	//cau de la plataforma es mori.
	playerInPlatform = false;
}

//Pinta els objectes
void GameManager::Draw()
{

	//Netegem el que es mostra per pantalla
	SDL_RenderClear(renderer);

	//Per cada element de l'escena
	for (auto obj : sceneObject)
	{
		//Pintem
		SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
	}

	//Recorrem les llistes
	for (int i=0; i<3;i++)
	{
		//Per cada element del riu
		for (DynamicObject obj : riverObjects[i])
		{
			//El coloquem al renderer
			SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
		}

		//Per cada element de la carretera
		for (DynamicObject obj : roadObjects[i])
		{
			//El coloquem al renderer
			SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
		}
	}

	//Coloquem la textura del personatge
	SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), &player.GetCollision());

	if(firstOccupied)SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), new SDL_Rect{ 30,0,player.GetCollision().w,player.GetCollision().h });
	if(secondOccupied)SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), new SDL_Rect{ 200,0,player.GetCollision().w,player.GetCollision().h });
	if(thirdOccupied)SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), new SDL_Rect{ 370,0,player.GetCollision().w,player.GetCollision().h });
	if(fourthOccupied)SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), new SDL_Rect{ 540,0,player.GetCollision().w,player.GetCollision().h });
	if(fifthOccupied)SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), new SDL_Rect{ 710,0,player.GetCollision().w,player.GetCollision().h });

	//Pintem tots elements del renderer
	SDL_RenderPresent(renderer);
}