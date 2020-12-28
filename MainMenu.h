#pragma once
#include "SFML/Graphics.hpp"

#define MAX_MENU_ITEMS 4
class MainMenu
{
	public:
		MainMenu(float width, float height);
		~MainMenu();

		void draw(sf::RenderWindow& window);
		void MoveUp();
		void MoveDown();
		int GetPressedItem();
private:
	int ItemIndex;
	sf::Font font;
	sf::Text text[MAX_MENU_ITEMS];
};

