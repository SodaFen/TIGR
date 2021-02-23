#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class cell
{
	public:
		cell();
		void setType(int type);
		void show(RenderWindow &window, int x, int y);
	protected:
		int coef;
		Sprite sprite;
		Texture texture;
};