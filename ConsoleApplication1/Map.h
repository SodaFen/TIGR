#pragma once
#include "cell.h"
#include <iostream>
#include <fstream>

class Map
{
	public:
		Map();
		void show(RenderWindow &window);
		void scrol(int vec);
		int** getMap();
		void chaneCell(int x, int y, int numb);
		int getNowX();
		int getNowY();
	protected:
		int** matr;
		cell* masCell;
		int sizex, sizey;
		int nowX, nowY, maxX, maxY;
};

