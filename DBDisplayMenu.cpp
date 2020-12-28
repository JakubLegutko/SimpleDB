#include "DBDisplayMenu.h"
DBDisplayMenu::DBDisplayMenu(float width, float height) {
	
	if (!font.loadFromFile("CreamySunset.ttf"))
	{
		//handle erorr
	}

	text[0].setFillColor(sf::Color::Green);
	text[0].setFont(font);
	text[0].setString("Odczytaj Baze");
	text[0].setPosition(sf::Vector2f(width*0.75 , height / (MAX_MENU_ITEMS + 1) * 1));

	text[1].setFillColor(sf::Color::White);
	text[1].setFont(font);
	text[1].setString("Wroc do menu glownego");
	text[1].setPosition(sf::Vector2f(width * 0.6, height / (MAX_MENU_ITEMS + 1) * 2));
	ItemIndex = 0;
}
DBDisplayMenu::~DBDisplayMenu()
{

}

void DBDisplayMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		window.draw(text[i]);
	}

}
void DBDisplayMenu::MoveUp() {
	if (ItemIndex - 1 >= 0)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex--;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}
void DBDisplayMenu::MoveDown() {
	if (ItemIndex + 1 < MAX_MENU_ITEMS)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex++;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}int DBDisplayMenu::GetPressedItem() {
	return ItemIndex;
}