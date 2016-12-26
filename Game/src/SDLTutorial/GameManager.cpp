#include "GameManager.h"



void GameManager::SceneInit()
{
	SDL_Rect forestCollision = { 0,0,WIDTH,80 };
	SDL_Rect forestImg = { 0,60,WIDTH,60 };
	Object forest(forestImg, forestCollision);
	sceneObject.push_back(forest);

	SDL_Rect waterCollision = { 0,70,WIDTH,150 };
	SDL_Rect waterImg = { 0,120,WIDTH,35 };
	Object water(waterImg, waterCollision);
	sceneObject.push_back(water);
}

void GameManager::DynamicsInit()
{
	//River Objects
	riverObjects = new vector<DynamicObject>[3];

	SDL_Rect woodCollision = { 0,70,WIDTH / 3,50 };
	SDL_Rect woodImg = { 7,165,180,25 };
	DynamicObject wood(woodImg, woodCollision, false,TYPE::PLATFORM);
	riverObjects[0].push_back(wood);

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
	riverObjects[2].push_back(wood);

	// Road Objects
	roadObjects = new vector<DynamicObject>[3];

	SDL_Rect carCollision = { 0,300,75,50 };
	SDL_Rect carImg = { 40,265,35,25 };
	DynamicObject car(carImg, carCollision, false, TYPE::ENEMY);
	roadObjects[2].push_back(car);

	carCollision = { WIDTH - 75,350,75,50 };
	carImg = { 80,265,35,25 };
	car.SetCollision(carCollision);
	car.SetImgBox(carImg);
	car.SetDirection(true);
	roadObjects[1].push_back(car);

	carCollision = { 0,400,75,50 };
	carImg = { 40,265,35,25 };
	car.SetCollision(carCollision);
	car.SetImgBox(carImg);
	car.SetDirection(false);
	roadObjects[0].push_back(car);

}

bool GameManager::Collision(DynamicObject & d, Rana & r)
{	
	int rYMax = r.GetCollision().y + r.GetCollision().h;
	int rXMax = r.GetCollision().x + r.GetCollision().w;

	int rXCenter = r.GetCollision().x + r.GetCollision().w / 2;
	int rYCenter = r.GetCollision().y + r.GetCollision().h / 2;

	int dYMax = d.GetCollision().y + d.GetCollision().h;
	int dXMax = d.GetCollision().x + d.GetCollision().w;
	int dXMin = d.GetCollision().x;
	int dYMin = d.GetCollision().y;


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
		SDL_Rect froggCollision = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
		SDL_Rect froggImg = { 10,360,25,25 };
		player.SetImgBox(froggImg);
		player.SetCollision(froggCollision);
		player.SetVidas(10);

		//Scene
		SceneInit();

		//Dynamic Objects
		DynamicsInit();
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

void GameManager::GameLoop()
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
					break;
				case SDL_KEYDOWN:
					SDL_Keycode key = evnt.key.keysym.sym;

					switch (key)
					{
					case SDLK_ESCAPE:
						isRunning = false;
						break;

					//Arrows
					case SDLK_UP:
						player.MoveUp();
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
						player.MoveUp();
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

void GameManager::Update()
{
	for (int i = 0; i<3; i++)
	{
		for (DynamicObject &obj : riverObjects[i])
		{
			obj.Update();
			if (Collision(obj, player))
			{
				playerInPlatform = true;
				if (!obj.GetDirection())
				{
					if (player.GetCollision().x + player.GetCollision().w < 800)
					{
						player.SetX(player.GetCollision().x + obj.GetVelociti());
					}
				}
				else
				{
					if (player.GetCollision().x > 0)
					{
						player.SetX(player.GetCollision().x - obj.GetVelociti());
					}
				}
			}
			else
			{
			}
		}
		for (DynamicObject &obj : roadObjects[i])
		{
			obj.Update();
			if (Collision(obj, player) && obj.GetType() == TYPE::ENEMY)
			{
				player.RestaVida();
				SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
				player.SetCollision(temp);
				cout << player.GetVidas() << endl;
			}
		}
	}
	if (player.GetCollision().y > 30 && player.GetCollision().y < 200 && !playerInPlatform)
	{
		player.RestaVida();
		SDL_Rect temp = { WIDTH / 2 - 50,HEIGTH - 50,50,50 };
		player.SetCollision(temp);
		cout << player.GetVidas() << endl;
	}
	playerInPlatform = false;
}

void GameManager::Draw()
{
	for (auto obj : sceneObject)
	{
		SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
	}
	for (int i=0; i<3;i++)
	{
		for (DynamicObject obj : riverObjects[i])
		{
			SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
		}
		for (DynamicObject obj : roadObjects[i])
		{
			SDL_RenderCopy(renderer, globalTexture, &obj.GetImgBox(), &obj.GetCollision());
		}
	}

	SDL_RenderCopy(renderer, globalTexture, &player.GetImgBox(), &player.GetCollision());
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
