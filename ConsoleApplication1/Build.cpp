#include "Build.h"

Build::Build() {

}

Build::~Build() {

}

void Build::actionTime() {

}

void Build::click() {

}

void Build::destr() {

}

void Build::buildTime() {

}

bool Build::getMoved() {
	return move;
}

void Build::setMoved(bool m) {
	move = m;
}

void Build::moved(int mousex, int mousey) {
	x = (mousex / 50) * 50;
	y = (mousey / 50) * 50;
}

void Build::CreatBuild(Map &m) {
	for(int i = 0; i < sizey; i++)
		for (int j = 0; j < sizex; j++)
			m.chaneCell((x / 50) + j, (y / 50) + i, 1);
}

int Build::getX() {
	return x;
}

int Build::getY() {
	return y;
}

void Build::setCreated(bool f) {
	created = f;
}

bool Build::getCreated() {
	return created;
}


void Build::byeBuilding(Map &m, int mouseX, int mouseY) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		setMoved(false);
		CreatBuild(m);
		setCreated(true);
		myX = m.getNowX();
		myY = m.getNowY();
		sprite.setPosition(x, y);
	}
	else {
		moved(mouseX, mouseY);
		sprite.setPosition(x, y);
	}
}

void Build::correctCord(int nowX, int nowY) {
	sprite.setPosition(x - (nowX - myX) * 50, y - (nowY - myY) * 50);
}