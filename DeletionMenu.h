#pragma once
#include "SFML/Graphics.hpp"

#define MAX_MENU_ITEMS 2
class DeletionMenu
{

public:
	DeletionMenu(float width, float height);
	~DeletionMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
private:
	int ItemIndex;
	sf::Font font;
	sf::Text text[MAX_MENU_ITEMS];
};
