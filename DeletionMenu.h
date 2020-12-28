#pragma once
#include "SFML/Graphics.hpp"

#define MAX_MENU_ITEMS 2
class DeletionMenu
{

public:
	DeletionMenu(float width, float height);
	~DeletionMenu();

	void update_amount(std::string amount_of_records);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

private:
	
	int ItemIndex;
	sf::Font font;
	sf::Text text[MAX_MENU_ITEMS];
	sf::Text display_avail[MAX_MENU_ITEMS];
};
