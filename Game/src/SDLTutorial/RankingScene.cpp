#include "RankingScene.h"


//Pinta
void RankingScene::Draw()
{
	//"Netejem el renderer"
	r->Clear();

	//Declarem la variable text i textLocation.
	string text;
	SDL_Rect textLocation;

	//Per cada element del ranking.
	for (int i = 0; i < 10; i++)
	{
		//Guardem la posicio, el nom i
		//l'score dintre l'string
		text = to_string(i + 1);
		text += ".- ";
		text += ranking->GetScoreByIndex(i).nom;
		text += "  ";
		text += to_string(ranking->GetScoreByIndex(i).punts);

		//Donem valor al SDL_Rect.
		textLocation = { 260,10 + (50 * i),250,40 };

		//L'introduim dintre el renderer.
		r->DrawText(text.c_str(), textLocation);
	}

	//Guardem el text "Press ENTER to continue"
	// a la variable text.
	text = "Press ENTER to continue";

	//Donem valor al SDL_Rect.
	textLocation = { 230,530,280,40 };

	//L'introduim dintre el renderer.
	r->DrawText(text.c_str(), textLocation);
	r->RenderPresent();

	/*SDL_RenderClear(r);

	//Declarem la variable text i textLocation.
	string text;
	SDL_Rect textLocation;

	//Per cada element del ranking.
	for (int i = 0; i < 10; i++)
	{
		//Guardem la posicio, el nom i
		//l'score dintre l'string
		text = to_string(i + 1);
		text += ".- ";
		text += ranking->GetScoreByIndex(i).nom;
		text += "  ";
		text += to_string(ranking->GetScoreByIndex(i).punts);

		//Donem valor al SDL_Rect.
		textLocation = { 260,10+(50*i),250,40 };

		//L'introduim dintre el renderer.
		RenderText(text.c_str(), textLocation);
	}

	//Guardem el text "Press ENTER to continue"
	// a la variable text.
	text = "Press ENTER to continue";

	//Donem valor al SDL_Rect.
	textLocation = { 230,530,280,40 };

	//L'introduim dintre el renderer.
	RenderText(text.c_str(), textLocation);

	//Pintem tots elements del renderer
	SDL_RenderPresent(r);*/
}

//Retorne el caracter de la tecla apretada
//Actualment no esta en us
char RankingScene::ObtenirNom(SDL_Keycode k)
{
	//Declarem les variables i les inicialitzem.
	string s = "";
	int a = 0;
	char c = ' ';

	//Convertim el num de la tecla en string
	s = to_string(k);

	//Convertim l'string a int
	a = stoi(s);

	//Convertim l'int a char.
	c = a;

	//Retorna c.
	return c;
}

//Constructor amb parametres pointer
//SDL_Renderer, GameState, Ranking, Rana
RankingScene::RankingScene(Renderer * renderer, GameState* g, Ranking* ran,Rana *p)
{
	r = renderer;
	gameState = g;
	difficult = nullptr;
	ranking = ran;
	player = p;
	firstTime = true;
}

//Destructor
RankingScene::~RankingScene()
{
	player = nullptr;
	ranking = nullptr;

	delete player;
	delete ranking;
}

void RankingScene::Loop()
{
	//Mentre ens volguem mantenir dintre l'escena
	for (bool isRunning = true; isRunning;)
	{
		//Si es dintre el top10 i es
		// la primera vagada que entre al bucle.
		if (ranking->IsTopTen(player->GetPuntuacion()) && firstTime && player->GetPuntuacion()>0)
		{
			//Declarem la variable name de tipus string
			// i la inicialitzem
			string name="";

			//Preguntem el nom al usuari.
			cout << "Escriu un nom (maxim 10 caracters)" << endl;
			
			//Llegeix el nom per teclat.
			cin >> name;

			//Afegeix el jugador dintre el ranking
			ranking->AddInTop(player->GetPuntuacion(), name.c_str());

			//Guarda el ranking.
			ranking->Save();

			//Ja no es la primera vagada que entre al bucle.
			firstTime = false;
		}
		else
		{
			//Declara la variable evnt.
			SDL_Event evnt;

			//Agafem l'event del SDL_PollEvent
			while (SDL_PollEvent(&evnt))
			{
				//Mirem de quin tipus es l'event.
				switch (evnt.type)
				{

					//Si a paretat una tecla
				case SDL_KEYDOWN:

					//Si la tecla es return
					if (evnt.key.keysym.sym == SDLK_RETURN)
					{
						//Indiquem que volem tornar al menu.
						isRunning = false;
						*gameState = GameState::MENU;
					}
					break;
				}
			}
			//Pinta.
			Draw();
		}
	}
}
