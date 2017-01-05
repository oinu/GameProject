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

struct Score
{
public:
	int punts;
	char nom[10];
	Score()
	{

	};
	Score(int p, char* c)
	{
		punts = p;
		for (int i = 0; i < 10; i++)
		{
			nom[i] = c[i];
		}
	}
};
class FileManager
{
	ofstream *writeBinaryFile;
	ifstream *readBinaryFile;
	xml_document<> *doc;
	xml_node<>*actualNode;
	xml_node<>*root;

public:
	FileManager()
	{
		doc = new xml_document<>();
	}

	~FileManager()
	{
		//Destruim els punter per si de cas.
		delete writeBinaryFile;
		delete readBinaryFile;
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
		if (file.is_open())
		{
			for (int i = 0; i < 10; i++)
			{
				file.read(reinterpret_cast<char*>(&ran[i].punts), sizeof(ran[i].punts));
				file.read(reinterpret_cast<char*>(&ran[i].nom), sizeof(ran[i].nom));
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				ran[i] = { 0,"NONE" };
			}
			WriteRankingAtFile(ran);
		}
		file.close();
		return ran;
	}

	int PlayerLives(Difficulty diff)
	{
		
		ifstream file("../../res/files/config.xml");
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		string content(buffer.str());

		
		doc->parse<0>(&content[0]);
		root = doc->first_node();
		actualNode = root;
		actualNode = actualNode->first_node("Difficulty");

		if (diff == Difficulty::EASE)
		{
			actualNode = actualNode->first_node("Ease");
		}
		else if (diff == Difficulty::MEDIUM)
		{
			actualNode = actualNode->first_node("Medium");
		}
		else
		{
			actualNode = actualNode->first_node("Hard");
		}

		actualNode = actualNode->first_node("Lives");
		return atoi(actualNode->value());
	}

	int CarVelocity(Difficulty diff)
	{
		ifstream file("../../res/files/config.xml");
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		string content(buffer.str());


		doc->parse<0>(&content[0]);
		root = doc->first_node();
		actualNode = root;
		actualNode = actualNode->first_node("Difficulty");

		if (diff == Difficulty::EASE)
		{
			actualNode = actualNode->first_node("Ease");
		}
		else if (diff == Difficulty::MEDIUM)
		{
			actualNode = actualNode->first_node("Medium");
		}
		else
		{
			actualNode = actualNode->first_node("Hard");
		}

		actualNode = actualNode->first_node("CarVelocity");
		return atoi(actualNode->value());
	}

	int WoodVelocity(Difficulty diff)
	{
		ifstream file("../../res/files/config.xml");
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		string content(buffer.str());


		doc->parse<0>(&content[0]);
		root = doc->first_node();
		actualNode = root;
		actualNode = actualNode->first_node("Difficulty");

		if (diff == Difficulty::EASE)
		{
			actualNode = actualNode->first_node("Ease");
		}
		else if (diff == Difficulty::MEDIUM)
		{
			actualNode = actualNode->first_node("Medium");
		}
		else
		{
			actualNode = actualNode->first_node("Hard");
		}

		actualNode = actualNode->first_node("WoodVelocity");
		return atoi(actualNode->value());
	}

	int TimePlayer(Difficulty diff)
	{
		ifstream file("../../res/files/config.xml");
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		string content(buffer.str());


		doc->parse<0>(&content[0]);
		root = doc->first_node();
		actualNode = root;
		actualNode = actualNode->first_node("Difficulty");

		if (diff == Difficulty::EASE)
		{
			actualNode = actualNode->first_node("Ease");
		}
		else if (diff == Difficulty::MEDIUM)
		{
			actualNode = actualNode->first_node("Medium");
		}
		else
		{
			actualNode = actualNode->first_node("Hard");
		}
		xml_node<> *divisor = actualNode;
		actualNode = actualNode->first_node("FroggTime");
		int num = atoi(actualNode->value());

		divisor = divisor->first_node("DivisorTime");
		float div = atof(divisor->value());

		return num/div;
	}

	int RiverElementsForLine(int lvl)
	{
		ifstream file("../../res/files/config.xml");
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		string content(buffer.str());


		doc->parse<0>(&content[0]);
		root = doc->first_node();
		actualNode = root;
		for (xml_node<> *pNode = root->first_node("Level"); pNode; pNode = pNode->next_sibling())
		{
			if (lvl == atoi(pNode->first_attribute()->value()))
			{
				actualNode = pNode;
			}
		}

		actualNode = actualNode->first_node("RiverElements");

		return atoi(actualNode->value());
	}

	int RoadElementsForLine(int lvl)
	{
		ifstream file("../../res/files/config.xml");
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		string content(buffer.str());


		doc->parse<0>(&content[0]);
		root = doc->first_node();
		actualNode = root;
		for (xml_node<> *pNode = root->first_node("Level"); pNode; pNode = pNode->next_sibling())
		{
			if (lvl == atoi(pNode->first_attribute()->value()))
			{
				actualNode = pNode;
			}
		}

		actualNode = actualNode->first_node("RoadElements");

		return atoi(actualNode->value());
	}
};
