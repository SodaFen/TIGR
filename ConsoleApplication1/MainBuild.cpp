#include "MainBuild.h"

MainBuild::MainBuild():Build() {
	texture.loadFromFile("C:\\Users\\vanon\\source\\repos\\ConsoleApplication1 (1)\\texturs\\MainBuild.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 150, 150));
	sizex = 3;
	sizey = 3;
}

void MainBuild::creatWorker() {

}

void MainBuild::show(RenderWindow& window) {
	//sprite.setPosition(x, y);
	if (getMoved()) {
		sprite.setColor(Color(255, 255, 255, 128));
		window.draw(sprite);
	}
	else {
		sprite.setColor(Color(255, 255, 255, 255));
		window.draw(sprite);
	}
}