#pragma once

class Rect
{
private:

	int width;
	int heigth;
	int x;
	int y;

public:
	
	//CONSTRUCTORS
	Rect()
	{
		x = 0;
		y = 0;
		width = 0;
		heigth = 0;
	};

	Rect(int aX, int aY, int aWidth, int aHeight)
		:x(aX), y(aY), width(aWidth), heigth(aHeight){};

	Rect(Rect &r)
	{
		x = r.x;
		y = r.y;
		width = r.width;
		heigth = r.heigth;
	}

	//FUNCTIONS
	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}
	
	int GetWidth()
	{
		return width;
	}

	int GetHeight()
	{
		return heigth;
	}

	void SetX(int value)
	{
		x = value;
	}

	void SetY(int value)
	{
		y = value;
	}

	void SetWidth(int value)
	{
		width = value;
	}

	void SetHeight(int value)
	{
		heigth = value;
	}
};