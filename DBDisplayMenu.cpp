#include "DBDisplayMenu.h"
DBDisplayMenu::DBDisplayMenu(float width, float height) {

	if (!font.loadFromFile("CreamySunset.ttf"))
	{
		//handle erorr
	}

	text[0].setFillColor(sf::Color::Green);
	text[0].setFont(font);
	text[0].setString("Odczytaj Baze");
	text[0].setPosition(sf::Vector2f(width * 0.774, height / (MAX_MENU_ITEMS_DISPLAY + 1) * 1));

	text[1].setFillColor(sf::Color::White);
	text[1].setFont(font);
	text[1].setString("Wroc do menu glownego");
	text[1].setPosition(sf::Vector2f(width * 0.61, height / (MAX_MENU_ITEMS_DISPLAY + 1) * 2));
	ItemIndex = 0;
	description[0].setFillColor(sf::Color::White);
	description[0].setFont(font);
	description[0].setString("Imie");
	description[0].setPosition(sf::Vector2f(width * 0.01, height / (MAX_RECORD_ITEMS + 1) * 1));
	description[1].setFillColor(sf::Color::White);
	description[1].setFont(font);
	description[1].setString("Nazwisko");
	description[1].setPosition(sf::Vector2f(width * 0.01, height / (MAX_RECORD_ITEMS + 1) * 2));
	description[2].setFillColor(sf::Color::White);
	description[2].setFont(font);
	description[2].setString("PESEL");
	description[2].setPosition(sf::Vector2f(width * 0.01, height / (MAX_RECORD_ITEMS + 1) * 3));
	description[3].setFillColor(sf::Color::White);
	description[3].setFont(font);
	description[3].setString("Wiek");
	description[3].setPosition(sf::Vector2f(width * 0.01, height / (MAX_RECORD_ITEMS + 1) * 4));
	description[4].setFillColor(sf::Color::White);
	description[4].setFont(font);
	description[4].setString("Bombelki");
	description[4].setPosition(sf::Vector2f(width * 0.01, height / (MAX_RECORD_ITEMS + 1) * 5));

}
DBDisplayMenu::~DBDisplayMenu()
{

}

void DBDisplayMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_MENU_ITEMS_DISPLAY; i++)
	{
		window.draw(text[i]);
	}
	for (int i = 0; i < MAX_RECORD_ITEMS; i++)
	{
		window.draw(description[i]);
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
	if (ItemIndex + 1 < MAX_MENU_ITEMS_DISPLAY)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex++;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}int DBDisplayMenu::GetPressedItem() {
	return ItemIndex;
}

