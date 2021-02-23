#include "cell.h"


cell::cell(){
	coef = 1;
}

void cell::setType(int type) {
	switch (type) {
		case 0:
			texture.loadFromFile("C:\\Users\\vanon\\source\\repos\\ConsoleApplication1 (1)\\texturs\\wall.png");
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 100, 100));
			sprite.setScale(0.5, 0.5);
			break;
		case 1:
			texture.loadFromFile("C:\\Users\\vanon\\source\\repos\\ConsoleApplication1 (1)\\texturs\\black.png");
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 50, 50));
			break;
		case 2:
			texture.loadFromFile("C:\\Users\\vanon\\source\\repos\\ConsoleApplication1 (1)\\texturs\\MainBuild.png");
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 150, 150));
			break;
	}
		
}

void cell::show(RenderWindow &window, int x, int y) {
	sprite.setPosition(x, y);
	window.draw(sprite);
}
