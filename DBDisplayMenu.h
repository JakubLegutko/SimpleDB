#pragma once
#include "SFML/Graphics.hpp"


#define MAX_MENU_ITEMS_DISPLAY 2
#define MAX_RECORD_ITEMS 5
class DBDisplayMenu
{

	public:
		DBDisplayMenu(float width, float height);
		~DBDisplayMenu();
		

		void draw(sf::RenderWindow& window);
		void MoveUp();
		void MoveDown();
		int GetPressedItem();
	private:
		int ItemIndex;
		sf::Font font;
		sf::Text text[MAX_MENU_ITEMS_DISPLAY];
		sf::Text description[MAX_RECORD_ITEMS];
		
};
