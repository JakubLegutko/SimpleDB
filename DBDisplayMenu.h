#pragma once
#include "SFML/Graphics.hpp"
#include "Textbox.cpp"

#define MAX_MENU_ITEMS_DISPLAY 3
#define MAX_RECORD_ITEMS 5
class DBDisplayMenu
{

	public:
		DBDisplayMenu(float width, float height);
		~DBDisplayMenu();
		Textbox wybor{ 20, sf::Color::White, false };
		sf::Text display[MAX_RECORD_ITEMS];
		void update_amount(std::string amount_of_records);
		void draw(sf::RenderWindow& window);
		void MoveUp();
		void MoveDown();
		int GetPressedItem();
	private:
		int ItemIndex;
		sf::Font font;
		sf::Text text[MAX_MENU_ITEMS_DISPLAY];
		sf::Text description[MAX_RECORD_ITEMS];
		sf::Text display_avail[2];
		
		
};
