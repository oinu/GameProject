#include "GameScene.h"
using namespace std;


//Retorna si hi ha hagut colisio entre la granota
// i algun element de tipus DynamicObject.
//Troncs i cotxes.
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

//Sobrescrivim el metode Collision, amb la finalitat
//de tambe saber si colisiona amb Objects,
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

//Pintem mentre juguem
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

	//Pintem el player
	player->Draw(r, t);

	//Si l'insecte es a l'escenari el pintem.
	if(!insectTake)insect.Draw(r, t);

	//Si una o varies de les caselles finals estan ocupades,
	//Pintem una granota el seu lloc.
	if (firstOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 30,0,player->GetCollision().w,player->GetCollision().h });
	if (secondOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 200,0,player->GetCollision().w,player->GetCollision().h });
	if (thirdOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 370,0,player->GetCollision().w,player->GetCollision().h });
	if (fourthOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 540,0,player->GetCollision().w,player->GetCollision().h });
	if (fifthOccupied)SDL_RenderCopy(r, t, &player->GetImgBox(), new SDL_Rect{ 710,0,player->GetCollision().w,player->GetCollision().h });

	//Pintem les vides, l'score i el temps que li queda
	//al jugador.
	string text = "Lives: ";
	text += to_string(player->GetVidas());
	text +=" Score: ";
	text += to_string(player->GetPuntuacion());
	text += " Time: ";
	text += to_string(playerTime);
	SDL_Rect textLocation = { 0,550,250,25 };
	RenderText(text.c_str(), textLocation);

	//Pintem tots elements del renderer
	SDL_RenderPresent(r);
}

//Pintem el menu pausa
void GameScene::DrawPause()
{
	//"Netejem el renderer"
	SDL_RenderClear(r);
	
	//Pintem el Resume text.
	string text = "Resume";
	SDL_Rect textLocation = { 300,150,200,50 };
	RenderText(text.c_str(), textLocation);

	//Pintem l'Exit text.
	text = "Exit";
	textLocation = { 350,400,100,50 };
	RenderText(text.c_str(), textLocation);

	//Pintem tots elements del renderer
	SDL_RenderPresent(r);
}

//Actualitzem els valors i comprovem colisions.
//accepcio del jugador.
void GameScene::Update()
{
	//Restem el temps al jugador
	DecreaseTime();

	//Coloquem l'insecte.
	InsertInsect();
	
	//Si la diferencie entre puntuacions es >= a 1000
	//Incrementem la velocitat.
	if (player->GetPuntuacion() - oldPuntuation >= 1000)
	{
		//Li donem el valor true
		incrementVelocity = true;

		//Agafem la puntacio actual del player
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

			//Si hi ha una diferencia de 1000 punts
			//S'incrementa la velocitat.
			if (incrementVelocity)obj.UpdateVelocity(player->GetPuntuacion());

			//Detectem si colisionen
			if (Collision(obj, *player))
			{
				//Si colisionen, li restem vida
				//i el coloquem el punt de partida
				player->RestaVida();
				player->PosInicial();
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
	}

	//li donem el valor a false amb la finalitat de que si
	//cau de la plataforma es mori.
	playerInPlatform = false;

	//Donem a incrementVelocity el valor de false
	//aixi nomes saltara quant toqui.
	incrementVelocity = false;
}

//Coloquem l'insecte dins l'escenari.
void GameScene::InsertInsect()
{
	//Creem una llavor que no vagi em el temps de rellotge
	srand(time(NULL));
	
	//Obtenim el temps actual 
	//i el guardem a insectCurrentTime
	time(insectCurrentTime);

	//Obtenim la diferencia de temps entre el current
	//i el saved i el guardem a la variable tmp.
	double tmp = difftime(*insectCurrentTime, *insectTimeSaved);

	//Declarem la variable per saber si s'ha de mostrar
	// o no l'insecte.
	bool randomPopUp=false;

	//Si esta preparat i a passat 2 segons
	if (insectPopUp && tmp >= 2)
	{
		//Donat un nombre random que es 0 o 1
		//Li donem aquest valor a la booleana randomPopUp
		randomPopUp = rand();

		//Si apareix, vol dir que ja s'ha fet pop
		insectPopUp = !randomPopUp;

		//Guardem el temps.
		time(insectTimeSaved);
	}
	//Si es dintre a l'escenari, a passat = o + de 5 segons
	//i ha estat colocat a dintre a l'escenari.
	else if (!insectPopUp && tmp >= 5 && !randomPopUp)
	{
		//Inidiquem que ha d'apareixa.
		insectPopUp = true;
		//Guardem el temps.
		time(insectTimeSaved);
		//I el treiem de l'escenari.
		insectTake = false;
	}
	
	//Si ha aparegut a l'escenari
	if (randomPopUp)
	{
		//Obtenim un valor random entre 1 i 5
		int randomNumber = rand() % 5 + 1;

		//Li donem un valor per defecte a la collisio
		// del insecte
		insect.SetCollision(player->GetCollision());

		//Obtenim la imatge de l'insecte
		SDL_Rect img = { 135,230,25,25 };

		//I li associem la imatge a l'objecte.
		insect.SetImgBox(img);

		//Declarem una variable temporal de tipus tmp
		SDL_Rect tmp;

		//Indiquem que no s'ha agafat l'insecte
		insectTake = false;

		//Comprovem el nombre resultant del random.
		switch (randomNumber)
		{
			//Si es 1
		case 1:
			//Mirem que la primera casella no estigui ocupada.
			if (!firstOccupied)
			{
				//Si no ho esta, li indiquem a la variable temp
				//Donantli de valor la posicio d'aquesta casella.
				tmp = { 30,10,player->GetCollision().w,player->GetCollision().h };

				//Indiquem que ja esta posat.
				randomPopUp = false;
			}
			break;

			//Si es 2
		case 2:
			if (!secondOccupied)
			{
				//Si no ho esta, li indiquem a la variable temp
				//Donantli de valor la posicio d'aquesta casella.
				tmp = { 200,10,player->GetCollision().w,player->GetCollision().h };
				//Indiquem que ja esta posat.
				randomPopUp = false;
			}
			break;

			//Si es 3
		case 3:
			if (!thirdOccupied)
			{
				//Si no ho esta, li indiquem a la variable temp
				//Donantli de valor la posicio d'aquesta casella.
				tmp = { 370,10,player->GetCollision().w,player->GetCollision().h };
				//Indiquem que ja esta posat.
				randomPopUp = false;
			}
			break;
			
			//Si es 4
		case 4:
			if (!fourthOccupied)
			{
				//Si no ho esta, li indiquem a la variable temp
				//Donantli de valor la posicio d'aquesta casella.
				tmp = { 540,10,player->GetCollision().w,player->GetCollision().h };
				//Indiquem que ja esta posat.
				randomPopUp = false;
			}
			break;

			//Si es 5
		case 5:
			if (!fifthOccupied)
			{
				//Si no ho esta, li indiquem a la variable temp
				//Donantli de valor la posicio d'aquesta casella.
				tmp = { 710,10,player->GetCollision().w,player->GetCollision().h };
				//Indiquem que ja esta posat.
				randomPopUp = false;
			}
			break;
			//Valor default, per si hi ha algun error.
		default:
			//Si no ho esta, li indiquem a la variable temp
			//Donantli de valor la posicio d'aquesta casella.
			tmp = player->GetCollision();
			break;
		}
		//Li donem el valor de tmp a l'insecte
		insect.SetCollision(tmp);	
	}
	
}

//Li treiem temps de vida al jugador.
void GameScene::DecreaseTime()
{
	//Guardem el temps actual
	time(playerCurrentTime);
	
	//Guardem la diferencia entre temps a la variable tmp
	double tmp = difftime(*playerCurrentTime, *playerTimeSaved);

	//Si ha passat 1 segon
	if (tmp >= 1)
	{
		//Li restem el temps del jugador.
		playerTime--;
		
		//Guardem el temps actual.
		time(playerTimeSaved);
	}

	//Si el jugador s'ha li acaba el temps
	if (playerTime == 0)
	{
		//Li restem una vida
		player->RestaVida();
		
		//Li donem el valor inicial al playerTime.
		playerTime = initalTime;

		//I el tornem a colocar al inici.
		player->PosInicial();
	}
}

//Constructor amb parametres, que son punters de tipus,
//SDL_Renderer,SDL_Texture,GameState,Rana,Difficulty i FilManager.
GameScene::GameScene(SDL_Renderer *renderer, SDL_Texture *global, GameState *state,Rana *rana,Difficulty* d, FileManager* f)
{
	r = renderer;
	t = global;
	gameState = state;
	level = 1;
	player = rana;
	difficult = d;
	oldPuntuation = 0;
	playerTime = 20;
	initalTime = 20;
	fileManager = f;
	playerCurrentTime = new time_t();
	playerTimeSaved = new time_t();
	insectTimeSaved = new time_t();
	insectCurrentTime = new time_t();
	insectPopUp = true;
}

//Destructor
GameScene::~GameScene()
{
	delete player;
	delete playerCurrentTime;
	delete playerTimeSaved;
	delete insectCurrentTime;
	delete insectTimeSaved;
}

//Loop de l'escena.
void GameScene::Loop()
{
	//Guardem el temps del player i de l'insecte
	time(playerTimeSaved);
	time(insectTimeSaved);

	try {
		//Declarem la variable que conte l'event
		SDL_Event evnt;

		//Mentre no sortim de l'escena
		for (bool isRunning = true; isRunning;)
		{
			//Si esta en joc.
			if (*gameState == GameState::GAME)
			{
				//INPUT HANDLER
				while (SDL_PollEvent(&evnt) && *gameState == GameState::GAME)
				{
					switch (evnt.type)
					{
						//Si apreta la creueta de la finestra, es tanca
					case SDL_QUIT:
						isRunning = false;
						*gameState = GameState::QUIT;
						break;
						
						//Si apreta una tecla
					case SDL_KEYDOWN:

						//La guardem a una variable SDL_Keycode
						SDL_Keycode key = evnt.key.keysym.sym;

						//Depenent de la tecla apretada
						switch (key)
						{
							//Si es escape pausa el joc
						case SDLK_ESCAPE:
							*gameState = GameState::PAUSE;
							break;

							//Arrows
						case SDLK_UP:
							//Si esta a l'ultim tronc
							if (player->GetCollision().y == 50)
							{
								//Comprova si la primera casella esta disponible
								if (!firstOccupied && player->GetCollision().x >= 20 && player->GetCollision().x <= 55)
								{
									//Si esta disponible mou el jugador
									//Activa la imatge dins la casella
									//El Coloca al inici
									player->MoveUp();

									//Detectem si ha hagut colisio amb l'insecte.
									if (Collision(insect, *player))
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(200);

										//Indiquem que ja l'han agafat.
										insectTake = true;
									}
									else
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(50);

										//Li sumem el temps * 10, tal i com indiquen
										//les especificacions.
										player->SumaPuntuacion(playerTime * 10);
									}

									//Indiquem que esta ocupat.
									firstOccupied = true;

									//Tornem el jugador a la posicio inicial.
									player->PosInicial();

									//Li donem el valor del temps del jugador,
									//al seu predeterminat.
									playerTime = initalTime;

								}
								//Comprova si la segona casella esta disponible
								else if (!secondOccupied && player->GetCollision().x >= 173 && player->GetCollision().x <= 225)
								{
									//Si esta disponible mou el jugador
									//Activa la imatge dins la casella
									//El Coloca al inici
									player->MoveUp();

									//Detectem si ha hagut colisio amb l'insecte
									if (Collision(insect, *player))
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(200);

										//Indiquem que ja l'han agafat.
										insectTake = true;
									}
									else
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(50);

										//Li sumem el temps * 10, tal i com indiquen
										//les especificacions.
										player->SumaPuntuacion(playerTime * 10);
									}

									//Indiquem que esta ocupat.
									secondOccupied = true;

									//Tornem el jugador a la posicio inicial.
									player->PosInicial();

									//Li donem el valor del temps del jugador,
									//al seu predeterminat.
									playerTime = initalTime;
								}
								//Comprova si la tercera casella esta disponible
								else if (!thirdOccupied && player->GetCollision().x >= 350 && player->GetCollision().x <= 400)
								{
									//Si esta disponible mou el jugador
									//Activa la imatge dins la casella
									//El Coloca al inici
									player->MoveUp();

									//Detectem si ha hagut colisio amb l'insecte
									if (Collision(insect, *player))
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(200);

										//Indiquem que ja l'han agafat.
										insectTake = true;
									}
									else
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(50);

										//Li sumem el temps * 10, tal i com indiquen
										//les especificacions.
										player->SumaPuntuacion(playerTime * 10);
									}

									//Indiquem que esta ocupat.
									thirdOccupied = true;

									//Tornem el jugador a la posicio inicial.
									player->PosInicial();

									//Li donem el valor del temps del jugador,
									//al seu predeterminat.
									playerTime = initalTime;
								}
								//Comprova si la quarta casella esta disponible
								else if (!fourthOccupied && player->GetCollision().x >= 520 && player->GetCollision().x <= 565)
								{
									//Si esta disponible mou el jugador
									//Activa la imatge dins la casella
									//El Coloca al inici
									player->MoveUp();

									//Detectem si ha hagut colisio amb l'insecte
									if (Collision(insect, *player))
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(200);

										//Indiquem que ja l'han agafat.
										insectTake = true;
									}
									else
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(50);

										//Li sumem el temps * 10, tal i com indiquen
										//les especificacions.
										player->SumaPuntuacion(playerTime * 10);
									}

									//Indiquem que esta ocupat.
									fourthOccupied = true;

									//Tornem el jugador a la posicio inicial.
									player->PosInicial();

									//Li donem el valor del temps del jugador,
									//al seu predeterminat.
									playerTime = initalTime;
								}
								//Comprova si la cinquena casella esta disponible
								else if (!fifthOccupied && player->GetCollision().x >= 700 && player->GetCollision().x <= 735)
								{
									//Si esta disponible mou el jugador
									//Activa la imatge dins la casella
									//El Coloca al inici
									player->MoveUp();

									//Detectem si ha hagut colisio amb l'insecte
									if (Collision(insect, *player))
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(200);

										//Indiquem que ja l'han agafat.
										insectTake = true;
									}
									else
									{
										//Li sumem a la puntuacio del jugador.
										player->SumaPuntuacion(50);

										//Li sumem el temps * 10, tal i com indiquen
										//les especificacions.
										player->SumaPuntuacion(playerTime * 10);
									}

									//Indiquem que esta ocupat.
									fifthOccupied = true;

									//Tornem el jugador a la posicio inicial.
									player->PosInicial();

									//Li donem el valor del temps del jugador,
									//al seu predeterminat.
									playerTime = initalTime;
								}

							}
							//Si no es a l'ultim tronc, abansa normal
							else
							{
								//Movem el jugador cap a dalt.
								player->MoveUp();

								//Si entre dintra la SafeZone, suma 10 punts.
								if (player->GetCollision().y == 200)
								{
									player->SumaPuntuacion(10);
								}
							}
							break;

							//Si apreta cap abaix
						case SDLK_DOWN:

							//El jugador es mou cap abaix
							player->MoveDown(600);
							break;

							//Si apreta cap a l'esquerra
						case SDLK_LEFT:

							//El jugador es mou cap a l'esquerra
							player->MoveLeft();
							break;

							//Si apreta cap a la dreta
						case SDLK_RIGHT:

							//El jugador es mou cap a la dreta
							player->MoveRight(800);
							break;
						default:
							break;
						}
					}

				}

				//Si les vides del jugador arriben a 0
				if (player->GetVidas() == 0)
				{
					//Canviem l'estat a GameOver
					*gameState = GameState::GAMEOVER;

					//Sortim de l'escena
					isRunning = false;
				}
				
				//Si s'han ocupat totes les posicions
				//canviem de nivell.
				else if (firstOccupied && secondOccupied && thirdOccupied
					&& fourthOccupied && fifthOccupied)
				{
					//Sumem 1000 punts al jugador.
					player->SumaPuntuacion(1000);

					//El coloquem a la posicio inicial.
					player->PosInicial();

					//I agumantem de nivell.
					if (level < 3)level++;

					//Canviar l'Start per un NextLvl
					Start();
				}

				//Si no, encara estem jugant al nivell actual.
				else
				{
					//UPDATE
					Update();

					//DRAW
					Draw();
				}
			}

			//Si esta en pause.
			else if (*gameState == GameState::PAUSE)
			{
				while (SDL_PollEvent(&evnt) && *gameState==GameState::PAUSE)
				{
					switch (evnt.type)
					{

						//Si fa clic amb el mouse.
					case SDL_MOUSEBUTTONDOWN:

						//Si esta dintre el quadrat del Resume
						if (evnt.button.y >= 150 && evnt.button.y <= 200
							&& (evnt.button.x >= 300 && evnt.button.x <= 500))
						{
							//Canviem el gameState a Game
							*gameState = GameState::GAME;
						}

						//Si esta dintre el quadrat de Exit
						else if (evnt.button.y >= 400 && evnt.button.y <= 450
							&& (evnt.button.x >= 300 && evnt.button.x <= 500))
						{
							//Sortim del bucle.
							isRunning = false;
							
							//Sortim al menu
							*gameState = GameState::MENU;
						}
						break;
					}
				}

				//Pintem el menu
				DrawPause();
			}
		}
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
}

//Inicialitzar variables
void GameScene::Start()
{
	//Insereix l'insecte.
	InsertInsect();

	//Declarem la variable carCollision,
	//i la inicialitzem amb una posicio en concret.
	SDL_Rect carCollision = { 0,300,75,50 };

	//Declarem la variable carImg
	//i la inicialitzem amb una posicio en concret.
	SDL_Rect carImg = { 40,265,35,25 };

	//Declarem i inicialitzem l'objecte
	//car del tipus DynamicObject,
	// amb els rectangles creats previament
	DynamicObject car(carImg, carCollision, false);

	//Li donem una distanica entre cotxes.
	car.SetDistance(100);

	//Declarem la variable woodCollision.
	SDL_Rect woodCollision;

	//Declarem la variable woodImg
	//i la inicialitzem amb una posicio en concret.
	SDL_Rect woodImg = { 7,165,180,25 };

	//Declarem i inicialitzem l'objecte
	//wood del tipus DynamicObject,
	// amb els rectangles creats previament
	DynamicObject wood(woodImg, woodCollision, false);

	//Li donem una distanica entre cotxes.
	wood.SetDistance(300);
	
	//Llegim del fileManager, les vides del jugador i les 
	//guardem dintre l'atribut del player.
	player->SetVidas(fileManager->PlayerLives(*difficult));

	//Llegim del fileManager, la velocitat dels cotxes i la 
	//guardem dintre el seu atribut.
	car.SetVelocity(fileManager->CarVelocity(*difficult));

	//Llegim del fileManager, la velocitat dels troncs i la 
	//guardem dintre el seu atribut.
	wood.SetVelocity(fileManager->WoodVelocity(*difficult));

	//Llegim del fileManager, el temps del jugador i el 
	//guardem a la variable initalTime.
	initalTime = fileManager->TimePlayer(*difficult);

	//Li donem al playerTime el temps inicial.
	playerTime = initalTime;

	//Desocupem totes les caselles finals.
	firstOccupied = false;
	secondOccupied = false;
	thirdOccupied = false;
	fourthOccupied = false;
	fifthOccupied = false;

	//Indiquem que el jugador no esta en una plataforma.
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
	riverLinesObjects = new vector<DynamicObject>[3];
	lastRiverObject = new DynamicObject*[3];
	
	//Llegim el nombre de troncs que hi haura per fila.
	riverElementsForLine = fileManager->RiverElementsForLine(level);
	
	//Declarem una variable que contindra la posicio en X
	// dels troncs, que comencen per la dreta, i la inicialitzem.
	int finalX = 800 - 800 / 3;

	//Declarem una variable que contidra la posicio en X
	// dels troncs que comencen per l'esquerra.
	int positionX;

	//Declarem la variable que contindra el width dels troncs.
	int width;
	
	//Afegim tants elements a les files, com indiquen
	//la configuracio.
	for (int i = 0; i < riverElementsForLine; i++)
	{
		//Indiquem la distancia
		wood.SetDistance(200);

		//Calculem la posicio en X.
		positionX = 0 - (800 / 3 * i + wood.GetDistance() * i);

		//Calculem el width.
		width = 800 / 3;

		//Guardem els valors dels parametres calculats.
		woodCollision = { positionX,70,width,50 };

		//Guardem els valors de la img.
		woodImg = { 7,165,180,25 };

		//Li donem el rectangle com a valor.
		wood.SetCollision(woodCollision);

		//Li donem el rectangle com a valor.
		wood.SetImgBox(woodImg);

		//Li indiquem el centit en que es moura.
		wood.SetDirection(false);

		//Afegim al vector de la seva fila.
		riverLinesObjects[2].push_back(wood);

		//Indiquem la distancia
		wood.SetDistance(200);

		//Calculem la posicio en X.
		positionX = finalX + (800 / 6 * i + wood.GetDistance() * i);
		
		//Calculem el width.
		width = 800 / 6;

		//Guardem els valors dels parametres calculats.
		woodCollision = { positionX,120,width,50 };

		//Guardem els valors de la img.
		woodImg = { 7,230,90,25 };

		//Li donem el rectangle com a valor.
		wood.SetCollision(woodCollision);

		//Li donem el rectangle com a valor.
		wood.SetImgBox(woodImg);

		//Li indiquem el centit en que es moura.
		wood.SetDirection(true);

		//Afegim al vector de la seva fila.
		riverLinesObjects[1].push_back(wood);

		//Indiquem la distancia
		wood.SetDistance(200);

		//Calculem la posicio en X.
		positionX = 0 - (((800 / 6) + 800 / 12) *i + wood.GetDistance() * i);
		
		//Calculem el width.
		width = (800 / 6) + 800 / 12;

		//Guardem els valors dels parametres calculats.
		woodCollision = { positionX,170,width,50 };

		//Guardem els valors de la img.
		woodImg = { 7,197,135,25 };

		//Li donem el rectangle com a valor.
		wood.SetCollision(woodCollision);

		//Li donem el rectangle com a valor.
		wood.SetImgBox(woodImg);

		//Li indiquem el centit en que es moura.
		wood.SetDirection(false);

		//Afegim al vector de la seva fila.
		riverLinesObjects[0].push_back(wood);


		//Quant arribem els ultims elements.
		if (i == riverElementsForLine-1)
		{
			//Apuntem, amb l'array de punters,
			//als ultims objectes
			lastRiverObject[0] = &riverLinesObjects[0][i];
			lastRiverObject[1] = &riverLinesObjects[1][i];
			lastRiverObject[2] = &riverLinesObjects[2][i];
		}
	}

	// Road Objects

	//Array de 3 elemetns, ja que son 3 files
	roadLinesObjects = new vector<DynamicObject>[5];
	lastRoadObject = new DynamicObject*[5];

	//Llegim els cotxes que hi haura per fila.
	roadElementsForLine = fileManager->RoadElementsForLine(level);

	//Utilitzem la formula indicada al document,
	//Per determinar el nombre d'elements.
	roadElementsForLine += (level - 1) % 3;

	//Redefinim el valor del finalX
	finalX = 800 - 75;

	//Afegim tants elements a les files, com indiquen
	//la configuracio.
	for (int i = 0; i < roadElementsForLine; i++)
	{
		//Guardem els valors dels parametres.
		carCollision = { finalX + (carCollision.w*i + car.GetDistance() * i),250,75,50 };

		//Guardem els valors de la img.
		carImg = { 110,295,40,25 };

		//Li donem el rectangle com a valor.
		car.SetCollision(carCollision);

		//Li donem el rectangle com a valor.
		car.SetImgBox(carImg);

		//Li indiquem el centit en que es moura.
		car.SetDirection(true);

		//Afegim al vector de la seva fila.
		roadLinesObjects[4].push_back(car);

		//Guardem els valors dels parametres.
		carCollision = { 0 - (carCollision.w*i + car.GetDistance() * i) ,300,75,50 };
		
		//Guardem els valors de la img.
		carImg = { 40,265,35,25 };

		//Li donem el rectangle com a valor.
		car.SetCollision(carCollision);

		//Li donem el rectangle com a valor.
		car.SetImgBox(carImg);

		//Li indiquem el centit en que es moura.
		car.SetDirection(false);

		//Afegim al vector de la seva fila.
		roadLinesObjects[3].push_back(car);

		//Guardem els valors dels parametres.
		carCollision = { finalX + (carCollision.w*i + car.GetDistance() * i),350,75,50 };
		
		//Guardem els valors de la img.
		carImg = { 10,265,35,25 };

		//Li donem el rectangle com a valor.
		car.SetCollision(carCollision);

		//Li donem el rectangle com a valor.
		car.SetImgBox(carImg);

		//Li indiquem el centit en que es moura.
		car.SetDirection(true);

		//Afegim al vector de la seva fila.
		roadLinesObjects[2].push_back(car);

		//Guardem els valors dels parametres.
		carCollision = { 0 - (carCollision.w*i + car.GetDistance() * i) ,400,75,50 };
		
		//Guardem els valors de la img.
		carImg = { 10,295,30,33 };

		//Li donem el rectangle com a valor.
		car.SetCollision(carCollision);

		//Li donem el rectangle com a valor.
		car.SetImgBox(carImg);

		//Li indiquem el centit en que es moura.
		car.SetDirection(false);

		//Afegim al vector de la seva fila.
		roadLinesObjects[1].push_back(car);

		//Guardem els valors dels parametres.
		carCollision = {finalX + (carCollision.w*i + car.GetDistance() * i),450,75,50 };
		
		//Guardem els valors de la img.
		carImg = { 80,265,35,25 };

		//Li donem el rectangle com a valor.
		car.SetCollision(carCollision);

		//Li donem el rectangle com a valor.
		car.SetImgBox(carImg);

		//Li indiquem el centit en que es moura.
		car.SetDirection(true);

		//Afegim al vector de la seva fila.
		roadLinesObjects[0].push_back(car);


		//Quant arribem els ultims elements.
		if (i == roadElementsForLine - 1)
		{
			//Apuntem, amb l'array de punters,
			//als ultims objectes.
			lastRoadObject[0] = &roadLinesObjects[0][i];
			lastRoadObject[1] = &roadLinesObjects[1][i];
			lastRoadObject[2] = &roadLinesObjects[2][i];
			lastRoadObject[3] = &roadLinesObjects[3][i];
			lastRoadObject[4] = &roadLinesObjects[4][i];
		}
	}
}
