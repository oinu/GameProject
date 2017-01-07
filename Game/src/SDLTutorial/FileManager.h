#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <XML\rapidxml.hpp>
#include <XML\rapidxml_iterators.hpp>
#include <XML\rapidxml_print.hpp>
#include <XML\rapidxml_utils.hpp>
#include "Enumerators.h"
using namespace std;
using namespace rapidxml;

//Estructura que s'utilitza
//per guardar/recuperar les posicions
struct Score
{
public:
	//Punts
	int punts;
	//Nom
	char nom[10];

	//Constructor per defecte
	Score()
	{

	};

	//Constructor per parametres
	Score(int p, const char* c)
	{
		punts = p;

		//D'aquesta forma ens assagurem de que
		//el nom es de maxim 10 caracters
		for (int i = 0; i < 10; i++)
		{
			nom[i] = c[i];
		}
	}
};

//Manager que obre i tanca fitxer
//Binaris i/o XML
class FileManager
{
	//Punter per escriure en fitxer binari.
	ofstream *writeBinaryFile;

	//Punter per llegir en fitxer binari.
	ifstream *readBinaryFile;

	//Punter que guarda el document XML llegit
	xml_document<> *doc;

	//Punter que conter el node en que treballem.
	xml_node<>*actualNode;

	//Punter que guarda la ubicació de l'arrel.
	xml_node<>*root;

public:
	//Contructor per defecte
	FileManager()
	{
		//El punter, ja no apunta a null
		doc = new xml_document<>();
	}

	//Destructor
	~FileManager()
	{
	}

	//Escriu en el document
	void WriteRankingAtFile(Score* ranking)
	{
		Score*r = ranking;
		ofstream file("../../res/files/ranking.dat", ios::out |ios::binary);
		for (int i = 0; i < 10; i++)
		{
			file.write(reinterpret_cast<char*>(&r[i].punts), sizeof(r[i].punts));
			file.write(reinterpret_cast<char*>(&r[i].nom), sizeof(r[i].nom));
		}
		file.close();
	}

	//Llegeix el document del ranking i 
	//Retorna un punter al ranking
	Score* ReadRankingAtFile()
	{
		//Prova d'obrir el document
		Score *ran = new Score[10];
		ifstream file("../../res/files/ranking.dat", ios::out | ios::binary);
		
		//Si el fitxer existeix i es obert
		if (file.is_open())
		{
			//Obtenim els 10 elements del document
			for (int i = 0; i < 10; i++)
			{
				//Llegim els punts i el nom
				file.read(reinterpret_cast<char*>(&ran[i].punts), sizeof(ran[i].punts));
				file.read(reinterpret_cast<char*>(&ran[i].nom), sizeof(ran[i].nom));
			}
		}
		//Sino, el creem.
		else
		{
			//Creem el ranking de 10
			for (int i = 0; i < 10; i++)
			{
				//Li donem el valor 0 i NONE
				//Perque no estigui buid el fitxer.
				ran[i] = { 0,"NONE" };
			}
			
			//Escrivim el fitxer.
			WriteRankingAtFile(ran);
		}

		//Tanquem el fitxer.
		file.close();

		//Returnem el punter del ranking
		return ran;
	}

	//Llegeix del document XML
	//Retorna el nombre de vides segons la dificultat
	int PlayerLives(Difficulty diff)
	{
		//Obrim el document xml
		ifstream file("../../res/files/config.xml");

		//Creem el buffer que contindra tot el document
		stringstream buffer;

		//Volquem la informacio del document al buffer
		buffer << file.rdbuf();

		//Tanquem el document
		file.close();

		//Convertim el buffer a una cadena de caracters
		string content(buffer.str());

		//Parsegem la cadena de caracters amb la finalitat
		//De recorre segons les etiquetes del XML
		doc->parse<0>(&content[0]);

		//Accedim el primer elment, que es l'arrel.
		root = doc->first_node();

		//Actualment apuntem a l'arrel
		actualNode = root;

		//A parti de l'arrel busquem l'etiqueta Difficulty
		actualNode = actualNode->first_node("Difficulty");

		//Si la dificultat seleccionada es Ease
		if (diff == Difficulty::EASE)
		{
			//Accedim el node que es digui Ease
			actualNode = actualNode->first_node("Ease");
		}

		//Si la dificultat seleccionada es Medium
		else if (diff == Difficulty::MEDIUM)
		{
			//Accdeim el node que es digui Medium
			actualNode = actualNode->first_node("Medium");
		}
		//Si no es cap de les anteriors
		//Vol dir que es Hard
		else
		{
			//Accedim el node que es digui Hard
			actualNode = actualNode->first_node("Hard");
		}

		//Una vagada seleccinat el node,
		//Accedim el node fill Lives
		actualNode = actualNode->first_node("Lives");

		//Accedim el seu valor i el convertim en int
		//per retornarlo
		return atoi(actualNode->value());
	}

	//Llegeix el document XML
	//Retorna la velocitat de cotxes que hi ha per carril
	int CarVelocity(Difficulty diff)
	{
		//LLegim el document
		ifstream file("../../res/files/config.xml");

		//Creem el buffer que contindra el document
		stringstream buffer;

		//Volquem el contingut del fitxer en el buffer
		buffer << file.rdbuf();

		//Tanquem el fitxer
		file.close();

		//Transformem tot el contingut del buffer
		//A una cadena un string.
		string content(buffer.str());

		//Parsegem el contingut de l'string per aixi tractarlo
		//Com a un XML
		doc->parse<0>(&content[0]);

		//Accedim el primer node, que es l'arrel.
		root = doc->first_node();

		//Actulament apuntem a l'arrel.
		actualNode = root;

		//Accedim el node fill Difficulty
		actualNode = actualNode->first_node("Difficulty");

		//Si la dificultat seleccionada es Ease
		if (diff == Difficulty::EASE)
		{
			//Accedim el node fill Ease
			actualNode = actualNode->first_node("Ease");
		}
		//Si la dificultat selecionada es Medium
		else if (diff == Difficulty::MEDIUM)
		{
			//Accedim el node fill Medium
			actualNode = actualNode->first_node("Medium");
		}
		//Si no es cap de les anteriors
		//Vol dir que la dificultat es Hard
		else
		{
			//Accedim el node fill Hard
			actualNode = actualNode->first_node("Hard");
		}

		//Accedim el node fill CarVelocity
		actualNode = actualNode->first_node("CarVelocity");

		//Convertim en int el contingut del node i el retornem
		return atoi(actualNode->value());
	}

	//Llegim el document XML
	//Retorna la velocitat dels troncs
	int WoodVelocity(Difficulty diff)
	{
		//Llegim el fitxer
		ifstream file("../../res/files/config.xml");

		//Creem el buffer que contindra la informacio.
		stringstream buffer;

		//Volquem el document al buffer
		buffer << file.rdbuf();

		//Tanquem el document
		file.close();

		//Volquem el contingut del buffer a l'string
		string content(buffer.str());

		//Parsegem el contingu de l'string
		//per tractarlo com un XML
		doc->parse<0>(&content[0]);

		//Accedim al primer node que es l'arrel.
		root = doc->first_node();

		//Actulament apuntem a l'arrel.
		actualNode = root;

		//Accedim el node fill que es diu Difficulty
		actualNode = actualNode->first_node("Difficulty");

		//Si la dificultat selecinada es Ease
		if (diff == Difficulty::EASE)
		{
			//Accedim el node fill Ease
			actualNode = actualNode->first_node("Ease");
		}
		//Si la dificultat selecinada es Medium
		else if (diff == Difficulty::MEDIUM)
		{
			//Accedim el node fill Medium
			actualNode = actualNode->first_node("Medium");
		}
		//Si no es cap dels casos anteriors
		//Vol dir que la dificultat es Hard
		else
		{
			//Accedim a node fill Hard
			actualNode = actualNode->first_node("Hard");
		}

		//Accedim el node fill WoodVelocity
		actualNode = actualNode->first_node("WoodVelocity");

		//Converitm el valor del node a int i el retornem
		return atoi(actualNode->value());
	}

	//Llegim el document XML
	//Retorna el temps que se li dona el jugador per vida
	int TimePlayer(Difficulty diff)
	{
		//Obrim el document
		ifstream file("../../res/files/config.xml");

		//Creem el buffer que contidra
		//el contingut del document.
		stringstream buffer;

		//Volquem el contingut del document al buffer
		buffer << file.rdbuf();

		//Tanquem el document
		file.close();

		//Convertim el contingut del buffer a un string
		string content(buffer.str());

		//Parseguem el contingut de l'string
		//per aixi tractarlo com un XML
		doc->parse<0>(&content[0]);

		//Accedim el primer node, que es l'arrel.
		root = doc->first_node();

		//Actualment apuntem a l'arrel.
		actualNode = root;

		//Accedim el node fill Difficulty
		actualNode = actualNode->first_node("Difficulty");

		//Si la dificultat selecionada es Ease
		if (diff == Difficulty::EASE)
		{
			//Accedim el node fill Ease
			actualNode = actualNode->first_node("Ease");
		}
		//Si la dificultat selecionada es Medium
		else if (diff == Difficulty::MEDIUM)
		{
			//Accedim el node fill Medium
			actualNode = actualNode->first_node("Medium");
		}
		//Si no es cap de les anteriors
		//Vol dir que la dificultat es Hard
		else
		{
			//Accedim el node fill Hard
			actualNode = actualNode->first_node("Hard");
		}
		//Creem un nou punter que sera igual al actual.
		xml_node<> *divisor = actualNode;

		//Amb l'actual accedim el node fill FroggTime
		actualNode = actualNode->first_node("FroggTime");

		//Accedim al valor, el convertim en un enter
		// i el guardem a una variable 
		int num = atoi(actualNode->value());

		//Amb l'actual accedim el node fill DivisorTime
		divisor = divisor->first_node("DivisorTime");

		//Accedim al valor, el convertim en un float
		// i el guardem a una variable 
		float div = atof(divisor->value());

		//Retornem el valor de dividir el temps de la granota
		//Amb el divisor marcat a les especificacions.
		return num/div;
	}

	//Llegim el document XML
	//Retorna el nombre de troncs que hi ha per fila
	int RiverElementsForLine(int lvl)
	{
		//Obrim el document
		ifstream file("../../res/files/config.xml");

		//Creem la variable buffer, que contindra
		//el contingut del document
		stringstream buffer;

		//Volquem el document al buffer.
		buffer << file.rdbuf();

		//Tanquem el document
		file.close();

		//Convertime el contingut del buffer a un string
		string content(buffer.str());

		//Parsegem el contingut de l'string
		//per aixi tractralo com un XML
		doc->parse<0>(&content[0]);

		//Accedim el primer node, que es l'arrel.
		root = doc->first_node();

		//Actualment apuntem a l'arrel.
		actualNode = root;

		//Per cada node fill que es digui Level
		for (xml_node<> *pNode = root->first_node("Level"); pNode; pNode = pNode->next_sibling())
		{
			//Accedim al valor del seu atribut i el converimt a un enter
			//El comparem amb el nivell actual, si es el mateix.
			if (lvl == atoi(pNode->first_attribute()->value()))
			{
				//Actual apuntar el node.
				actualNode = pNode;
			}
		}
		//Accedim el node fill RiverElements
		actualNode = actualNode->first_node("RiverElements");
		
		//Convertim el valor del node en enter i el retornem.
		return atoi(actualNode->value());
	}

	//Llegim el document XML
	//Retorna el nombre de cotxes que hi ha per fila
	int RoadElementsForLine(int lvl)
	{
		//Obrim el document
		ifstream file("../../res/files/config.xml");

		//Declarem la variable buffer.
		stringstream buffer;

		//Volquem el contingut del fitxer.
		buffer << file.rdbuf();

		//Tanquem el fitxer.
		file.close();

		//Convertim el contingut del buffer en un string.
		string content(buffer.str());

		//Parsegem el contingut de l'string per aixi
		//Tractarlo com un XML
		doc->parse<0>(&content[0]);

		//Accedim el primer node que es l'arrel.
		root = doc->first_node();

		//Actualment apuntem a l'arrel.
		actualNode = root;

		//Per cada node fill anomenat Level
		for (xml_node<> *pNode = root->first_node("Level"); pNode; pNode = pNode->next_sibling())
		{
			//Accedim al contingut del seu atribut i
			//el convertim en un enter per copararlo amb el nivell actual.
			if (lvl == atoi(pNode->first_attribute()->value()))
			{
				//Si es el nivell, actual apunta el node
				actualNode = pNode;
			}
		}

		//Accedim el node fill RoadElements
		actualNode = actualNode->first_node("RoadElements");

		//Agafem el valor del node i
		//el convertim en un enter, i el retornem
		return atoi(actualNode->value());
	}
};
