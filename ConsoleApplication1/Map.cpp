#include "Map.h"

Map::Map() {
	std::ifstream fin("C:\\Users\\vanon\\source\\repos\\ConsoleApplication1 (1)\\Map\\Map.txt");
	fin >> maxX;
	fin >> maxY;
	sizex = 39;
	sizey = 22;
	nowX = 0;
	nowY = 0;
	matr = new int * [maxY];
	for (int i = 0; i < maxY; i++) {
		matr[i] = new  int [maxX];
		for (int j = 0; j < maxX; j++)
			fin >> matr[i][j];
	}
	masCell = new cell[2];
	masCell[0].setType(0);
	masCell[1].setType(1);
}

void Map::show(RenderWindow &window) {
	for (int i = nowY; i < sizey; i++)
		for (int j = nowX; j < sizex; j++)
			masCell[matr[i][j]].show(window, (j - nowX) * 50, (i - nowY) * 50);
}

void Map::scrol(int vec) {
	switch (vec){
		case 1:
			if (nowY > 0) {
				nowY--;
				sizey--;
			}
			break;
		case 2:
			if(sizey < maxY){
				nowY++;
				sizey++;
			}
			break;
		case 3:
			if (nowX > 0) {
				nowX--;
				sizex--;
			}
			break;
		case 4:
			if (sizex < maxX) {
				nowX++;
				sizex++;
			}
			break;
	}
}

int** Map::getMap() {
	return matr;
}

void Map::chaneCell(int x, int y, int numb) {
	matr[nowY + y][nowX + x] = numb;
}

int Map::getNowY() {
	return nowY;
}

int Map::getNowX() {
	return nowX;
}