#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include "Map.h"
#include "MainBuild.h"

using namespace sf;
void mouseScroll(Map &m, std::vector <MainBuild>& mb);

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "TestGame", Style::Fullscreen); //Style::Fullscreen	
	window.setFramerateLimit(60);

	Map m;
	std::vector <MainBuild> mb;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
	
		mouseScroll(m, mb);

		m.show(window);

		if (Mouse::isButtonPressed(Mouse::Right)) {			
			mb.push_back(MainBuild());
			mb[mb.size() - 1].setCreated(false);
			mb[mb.size() - 1].setMoved(true);
		}
		if (!mb.empty()) {
			if (mb[mb.size() - 1].getMoved()) {
				mb[mb.size() - 1].byeBuilding(m, Mouse::getPosition().x, Mouse::getPosition().y);
				mb[mb.size() - 1].show(window);
			}
			for (int i = 0; i < mb.size(); i++) {
				if (mb[i].getCreated())
					mb[i].show(window);
			}
		}

		window.display();		
	}

	return 0;
}

void mouseScroll(Map &m, std::vector <MainBuild> &mb) {
	if (Mouse::getPosition().y <= 20)
		m.scrol(1);
	if (Mouse::getPosition().y >= 1060)
		m.scrol(2);
	if (Mouse::getPosition().x <= 20)
		m.scrol(3);
	if (Mouse::getPosition().x >= 1900)
		m.scrol(4);
	for(int i = 0; i < mb.size(); i++)
		if(mb[i].getCreated())
			mb[i].correctCord(m.getNowX(), m.getNowY());
}