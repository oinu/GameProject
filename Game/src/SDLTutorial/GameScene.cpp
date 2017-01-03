#include "GameScene.h"



bool GameScene::Collision(DynamicObject & d, Rana & r)
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
	bool collVertical = dYMin <= rYCenter && dYMax >= rYCenter;
	bool collLateral = dXMin <= rXCenter && dXMax >= rXCenter;

	if (collLateral  && collVertical)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameScene::Draw()
{
	//Netegem el que es mostra per pantalla
	SDL_RenderClear(r);

	//Per cada element de l'escena
	for (auto obj : sceneObject)
	{
		//Pintem
		//SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
		obj.Draw(r, t);
	}

	//Recorrem les llistes
	for (int i = 0; i<3; i++)
	{
		//Per cada element del riu
		for (DynamicObject obj : riverObjects[i])
		{
			//El coloquem al renderer
			//SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
			obj.Draw(r, t);
		}

		//Per cada element de la carretera
		for (DynamicObject obj : roadObjects[i])
		{
			//El coloquem al renderer
			//SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
			obj.Draw(r, t);
		}
	}

	//Coloquem la textura del personatge
	//SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), &player.GetCollision());
	player->Draw(r, t);

	if (firstOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 30,0,player->GetCollision().w,player->GetCollision().h });
	if (secondOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 200,0,player->GetCollision().w,player->GetCollision().h });
	if (thirdOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 370,0,player->GetCollision().w,player->GetCollision().h });
	if (fourthOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 540,0,player->GetCollision().w,player->GetCollision().h });
	if (fifthOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 710,0,player->GetCollision().w,player->GetCollision().h });

	//Pintem tots elements del renderer
	SDL_RenderPresent(r);
}

void GameScene::Update()
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
			if (Collision(obj, *player))
			{
				//En cas afirmatiu
				//diguem que esta sobre una plataforma
				playerInPlatform = true;

				//Si va de dreta a esquerra
				if (!obj.GetDirection() && (player->GetCollision().x + player->GetCollision().w < 800))
				{
					player->SetX(player->GetCollision().x + obj.GetVelociti());
				}

				//Si va d'esquerra a dreta
				else
				{
					if (player->GetCollision().x > 0)
					{
						player->SetX(player->GetCollision().x - obj.GetVelociti());
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
			if (Collision(obj, *player))
			{
				//Si colisionen, li restem vida
				//i el coloquem el punt de partida
				player->RestaVida();
				SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
				player->SetCollision(temp);
				cout << player->GetVidas() << endl;
			}
		}
	}

	//Si el jugador és dintre de l'aigua
	//i no esta sobre una plataforma
	if (player->GetCollision().y > 30 && player->GetCollision().y < 200 && !playerInPlatform)
	{
		//Si colisionen, li restem vida
		//i el coloquem el punt de partida
		player->RestaVida();
		SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
		player->SetCollision(temp);
		cout << player->GetVidas() << endl;
	}

	//li donem el valor a false amb la finalitat de que si
	//cau de la plataforma es mori.
	playerInPlatform = false;
}

GameScene::GameScene(SDL_Renderer *renderer, SDL_Texture *global, GameState *state,int lvl,Rana *rana)
{
	r = renderer;
	t = global;
	gameState = state;
	level = lvl;
	player = rana;

	// Paret verda
	SDL_Rect forestCollision = { 0,0,800,80 };
	SDL_Rect forestImg = { 0,60,800,60 };
	Object forest(forestImg, forestCollision);
	sceneObject.push_back(forest);

	//Riu
	SDL_Rect waterCollision = { 0,70,800,150 };
	SDL_Rect waterImg = { 0,120,800,35 };
	Object water(waterImg, waterCollision);
	sceneObject.push_back(water);

	//River Objects

	//Array de 3 elemetns, ja que son 3 files
	riverObjects = new vector<DynamicObject>[3];

	SDL_Rect woodCollision;
	SDL_Rect woodImg = { 7,165,180,25 };
	DynamicObject wood(woodImg, woodCollision, false);
	int finalX = 800 - 800 / 3;

	for (int i = 0; i < 3; i++)
	{
		woodCollision = { 0 - (woodCollision.w*i + 100 * i),70,800 / 3,50 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(false);
		riverObjects[2].push_back(wood);

		woodCollision = { finalX + (woodCollision.w*i + 100 * i),120,800 / 3,50 };
		woodImg = { 7,165,180,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(true);
		riverObjects[1].push_back(wood);

		woodCollision = { 0 - (woodCollision.w*i + 100 * i),170,800 / 3,50 };
		woodImg = { 7,165,180,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(false);
		riverObjects[0].push_back(wood);
	}

	// Road Objects

	//Array de 3 elemetns, ja que son 3 files
	roadObjects = new vector<DynamicObject>[3];
	finalX = 800 - 75;

	SDL_Rect carCollision = { 0,300,75,50 };
	SDL_Rect carImg = { 40,265,35,25 };
	DynamicObject car(carImg, carCollision, false);

	for (int i = 0; i < 3; i++)
	{
		carCollision = { 0 - (carCollision.w*i + 100 * i),300,75,50 };
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

GameScene::~GameScene()
{
}

void GameScene::Loop()
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
					*gameState = GameState::QUIT;
					break;
				case SDL_KEYDOWN:
					SDL_Keycode key = evnt.key.keysym.sym;

					switch (key)
					{
					case SDLK_ESCAPE:
						isRunning = false;
						*gameState = GameState::QUIT;
						break;

						//Arrows
					case SDLK_UP:
						//Si esta a l'ultim tronc
						if (player->GetCollision().y == 50)
						{
							//Comprova si les caselles estan disponibles
							if (!firstOccupied && player->GetCollision().x >= 20 && player->GetCollision().x <= 55)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								firstOccupied = true;
								SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
								player->SetCollision(temp);
							}
							else if (!secondOccupied && player->GetCollision().x >= 173 && player->GetCollision().x <= 225)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								secondOccupied = true;
								SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
								player->SetCollision(temp);
							}
							else if (!thirdOccupied && player->GetCollision().x >= 350 && player->GetCollision().x <= 400)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								thirdOccupied = true;
								SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
								player->SetCollision(temp);
							}
							else if (!fourthOccupied && player->GetCollision().x >= 520 && player->GetCollision().x <= 565)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								fourthOccupied = true;
								SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
								player->SetCollision(temp);
							}
							else if (!fifthOccupied && player->GetCollision().x >= 700 && player->GetCollision().x <= 735)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								fifthOccupied = true;
								SDL_Rect temp = { 800 / 2 - 50,600 - 50,50,50 };
								player->SetCollision(temp);
							}

						}
						//Si no es a l'ultim tronc, abansa normal
						else player->MoveUp();
						break;
					case SDLK_DOWN:
						player->MoveDown(600);
						break;
					case SDLK_LEFT:
						player->MoveLeft();
						break;
					case SDLK_RIGHT:
						player->MoveRight(800);
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
