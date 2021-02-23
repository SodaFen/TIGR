#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace sf;

class Build
{
	public:
		Build();
		~Build();
		virtual void show(RenderWindow& window) = 0;
		virtual void click();
		virtual void actionTime();
		virtual void buildTime();
		virtual void destr();
		virtual void moved(int mousex, int mousey);
		virtual bool getMoved();
		virtual void setMoved(bool m);
		virtual void CreatBuild(Map &m);
		virtual int getX();
		virtual int getY();
		virtual void byeBuilding(Map &m, int mouseX, int mouseY);
		virtual void setCreated(bool f);
		virtual bool getCreated();
		virtual void correctCord(int nowX, int nowY);

	protected:
		int sizex, sizey;
		int strength;
		Sprite sprite;
		Texture texture;
		int x, y;
		int cost;
		bool move, created;
		int myX, myY;

};

