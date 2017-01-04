#include "GameScene.h"
using namespace std;



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
bool GameScene::Collision(Object & d, Rana & r)
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
		for (DynamicObject obj : riverLinesObjects[i])
		{
			//El coloquem al renderer
			//SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
			obj.Draw(r, t);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		//Per cada element de la carretera
		for (DynamicObject obj : roadLinesObjects[i])
		{
			//El coloquem al renderer
			//SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
			obj.Draw(r, t);
		}
	}

	//Coloquem la textura del personatge
	//SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), &player.GetCollision());
	player->Draw(r, t);
	if(!insectTake)insect.Draw(r, t);

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
	
	if (player->GetPuntuacion() - oldPuntuation >= 1000)
	{
		incrementVelocity = true;
		oldPuntuation = player->GetPuntuacion();
	}

	//Per cada element de la llista
	for (int i = 0; i<3; i++)
	{
		//Recorrem tots el objectes del riu
		for (DynamicObject &obj : riverLinesObjects[i])
		{
			//Els actualitzem
			obj.Update(lastRiverObject[i]);
			if(incrementVelocity)obj.UpdateVelocity(player->GetPuntuacion());

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
	}
	
	for (int i = 0; i < 5; i++)
	{
		//Recorrem tots els objectes de la carretera
		for (DynamicObject &obj : roadLinesObjects[i])
		{
			//Els actualitzem
			obj.Update(lastRoadObject[i]);
			if (incrementVelocity)obj.UpdateVelocity(player->GetPuntuacion());

			//Detectem si colisionen
			if (Collision(obj, *player))
			{
				//Si colisionen, li restem vida
				//i el coloquem el punt de partida
				player->RestaVida();
				player->PosInicial();
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
		player->PosInicial();
		cout << player->GetVidas() << endl;
	}

	//li donem el valor a false amb la finalitat de que si
	//cau de la plataforma es mori.
	playerInPlatform = false;
	incrementVelocity = false;
}

void GameScene::InsertInsect()
{
	srand(time(NULL));
	int randomNumber = rand() % 5 + 1;
	insect.SetCollision(player->GetCollision());
	SDL_Rect img= { 135,230,25,25 };
	insect.SetImgBox(img);
	SDL_Rect tmp;
	insectTake = false;

	switch (randomNumber)
	{
	case 1:
		if (!firstOccupied)
		{
			tmp={ 30,10,player->GetCollision().w,player->GetCollision().h };
		}
		break;
	case 2:
		if (!secondOccupied)
		{
			tmp = { 200,10,player->GetCollision().w,player->GetCollision().h };
		}
		break;
	case 3:
		if (!thirdOccupied)
		{
			tmp = { 370,10,player->GetCollision().w,player->GetCollision().h };
		}
		break;
	case 4:
		if (!fourthOccupied)
		{
			tmp = { 540,10,player->GetCollision().w,player->GetCollision().h };
		}
		break;
	case 5:
		if (!fifthOccupied)
		{
			tmp = { 710,10,player->GetCollision().w,player->GetCollision().h };
		}
		break;
	default:
		tmp = player->GetCollision();
		cout << randomNumber;
		break;
	}
	insect.SetCollision(tmp);
}

GameScene::GameScene(SDL_Renderer *renderer, SDL_Texture *global, GameState *state,Rana *rana,Difficulty* d)
{
	r = renderer;
	t = global;
	gameState = state;
	level = 1;
	player = rana;
	difficult = d;
	oldPuntuation = 0;
	currentTime = 20;
	initalTime = 20;
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
								if (Collision(insect, *player))
								{
									player->SumaPuntuacion(200);
									insectTake = true;
								}
								else player->SumaPuntuacion(50);
								std::cout << player->GetPuntuacion() << endl;
								firstOccupied = true;
								player->PosInicial();
								
							}
							else if (!secondOccupied && player->GetCollision().x >= 173 && player->GetCollision().x <= 225)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								if (Collision(insect, *player))
								{
									player->SumaPuntuacion(200);
									insectTake = true;
								}
								else player->SumaPuntuacion(50);
								cout << player->GetPuntuacion() << endl;
								secondOccupied = true;
								player->PosInicial();
							}
							else if (!thirdOccupied && player->GetCollision().x >= 350 && player->GetCollision().x <= 400)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								if (Collision(insect, *player))
								{
									player->SumaPuntuacion(200);
									insectTake = true;
								}
								else player->SumaPuntuacion(50);
								cout << player->GetPuntuacion() << endl;
								thirdOccupied = true;
								player->PosInicial();
							}
							else if (!fourthOccupied && player->GetCollision().x >= 520 && player->GetCollision().x <= 565)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								if (Collision(insect, *player))
								{
									player->SumaPuntuacion(200);
									insectTake = true;
								}
								else player->SumaPuntuacion(50);
								cout << player->GetPuntuacion() << endl;
								fourthOccupied = true;
								player->PosInicial();
							}
							else if (!fifthOccupied && player->GetCollision().x >= 700 && player->GetCollision().x <= 735)
							{
								//Si esta disponible mou el jugador
								//Activa la imatge dins la casella
								//El Coloca al inici
								player->MoveUp();
								if (Collision(insect, *player))
								{
									player->SumaPuntuacion(200);
									insectTake = true;
								}
								else player->SumaPuntuacion(50);
								cout << player->GetPuntuacion() << endl;
								fifthOccupied = true;
								player->PosInicial();
							}

						}
						//Si no es a l'ultim tronc, abansa normal
						else
						{
							player->MoveUp();
							if(player->GetCollision().y==200)
							{
								player->SumaPuntuacion(10);
							}
							cout << player->GetPuntuacion() << endl;
						}
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
			if (player->GetVidas() == 0)
			{
				*gameState = GameState::MENU;
				isRunning = false;
			}
			else if (firstOccupied && secondOccupied && thirdOccupied
				&& fourthOccupied && fifthOccupied)
			{
				player->SumaPuntuacion(1000);
				player->PosInicial();

				//Canviar l'Start per un NextLvl
				Start();
			}
			else
			{
				//UPDATE
				Update();

				//DRAW
				Draw();
			}
		}
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
}

void GameScene::Start()
{
	InsertInsect();
	SDL_Rect carCollision = { 0,300,75,50 };
	SDL_Rect carImg = { 40,265,35,25 };
	DynamicObject car(carImg, carCollision, false);
	car.SetDistance(100);

	SDL_Rect woodCollision;
	SDL_Rect woodImg = { 7,165,180,25 };
	DynamicObject wood(woodImg, woodCollision, false);
	wood.SetDistance(200);

	if (*difficult == Difficulty::EASE)
	{
		player->SetVidas(10);
		car.SetVelocity(1);
		wood.SetVelocity(1);
		initalTime = 20;
	}
	else if (*difficult == Difficulty::MEDIUM)
	{
		player->SetVidas(5);
		car.SetVelocity(2);
		wood.SetVelocity(2);
		initalTime = 20/1.5;
	}
	else
	{
		player->SetVidas(1);
		car.SetVelocity(3);
		wood.SetVelocity(3);
		initalTime = 20 / 2.5;
	}

	firstOccupied = false;
	secondOccupied = false;
	thirdOccupied = false;
	fourthOccupied = false;
	fifthOccupied = false;
	playerInPlatform = false;

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
	riverElementsForLine = 5;
	roadElementsForLine = 5;

	riverLinesObjects = new vector<DynamicObject>[3];
	lastRiverObject = new DynamicObject*[3];

	
	int finalX = 800 - 800 / 3;
	int positionX;
	int width;
	
	for (int i = 0; i < riverElementsForLine; i++)
	{
		//wood.SetDistance(200)
		positionX = 0 - (800 / 3 * i + wood.GetDistance() * i);
		width = 800 / 3;

		woodCollision = { positionX,70,width,50 };
		woodImg = { 7,165,180,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(false);
		riverLinesObjects[2].push_back(wood);

		positionX = finalX + (800 / 6 * i + wood.GetDistance() * i);
		width = 800 / 6;

		woodCollision = { positionX,120,width,50 };
		woodImg = { 7,230,90,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(true);
		riverLinesObjects[1].push_back(wood);

		positionX = 0 - (((800 / 6) + 800 / 12) *i + wood.GetDistance() * i);
		width = (800 / 6) + 800 / 12;

		woodCollision = { positionX,170,width,50 };
		woodImg = { 7,197,135,25 };
		wood.SetCollision(woodCollision);
		wood.SetImgBox(woodImg);
		wood.SetDirection(false);
		riverLinesObjects[0].push_back(wood);

		if (i == riverElementsForLine-1)
		{
			lastRiverObject[0] = &riverLinesObjects[0][i];
			lastRiverObject[1] = &riverLinesObjects[1][i];
			lastRiverObject[2] = &riverLinesObjects[2][i];
		}
	}

	// Road Objects

	//Array de 3 elemetns, ja que son 3 files
	roadLinesObjects = new vector<DynamicObject>[5];
	lastRoadObject = new DynamicObject*[5];
	finalX = 800 - 75;

	for (int i = 0; i < roadElementsForLine; i++)
	{
		carCollision = { finalX + (carCollision.w*i + car.GetDistance() * i),250,75,50 };
		carImg = { 110,295,40,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(true);
		roadLinesObjects[4].push_back(car);

		carCollision = { 0 - (carCollision.w*i + car.GetDistance() * i) ,300,75,50 };
		carImg = { 40,265,35,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(false);
		roadLinesObjects[3].push_back(car);

		carCollision = { finalX + (carCollision.w*i + car.GetDistance() * i),350,75,50 };
		carImg = { 10,265,35,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(true);
		roadLinesObjects[2].push_back(car);

		carCollision = { 0 - (carCollision.w*i + car.GetDistance() * i) ,400,75,50 };
		carImg = { 10,295,30,33 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(false);
		roadLinesObjects[1].push_back(car);

		carCollision = {finalX + (carCollision.w*i + car.GetDistance() * i),450,75,50 };
		carImg = { 80,265,35,25 };
		car.SetCollision(carCollision);
		car.SetImgBox(carImg);
		car.SetDirection(true);
		roadLinesObjects[0].push_back(car);

		if (i == roadElementsForLine - 1)
		{
			lastRoadObject[0] = &roadLinesObjects[0][i];
			lastRoadObject[1] = &roadLinesObjects[1][i];
			lastRoadObject[2] = &roadLinesObjects[2][i];
			lastRoadObject[3] = &roadLinesObjects[3][i];
			lastRoadObject[4] = &roadLinesObjects[4][i];
		}
	}
}
