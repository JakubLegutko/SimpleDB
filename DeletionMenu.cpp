#include "DeletionMenu.h"
#include <string>
#include <iostream>
DeletionMenu::DeletionMenu(float width, float height) {

	if (!font.loadFromFile("CreamySunset.ttf")) font.loadFromFile("C:\Windows\Fonts\Arial.ttf");//Case font is not found, use windows arial font

	text[0].setFillColor(sf::Color::Green);
	text[0].setFont(font);
	text[0].setString("Usun Rekord");
	text[0].setPosition(sf::Vector2f(width * 0.75, height / (MAX_MENU_ITEMS + 1) * 1));

	text[1].setFillColor(sf::Color::White);
	text[1].setFont(font);
	text[1].setString("Wroc do menu glownego");
	text[1].setPosition(sf::Vector2f(width * 0.6, height / (MAX_MENU_ITEMS + 1) * 2));
	ItemIndex = 0;
	display_avail[0].setFillColor(sf::Color::White);
	display_avail[0].setFont(font);
	display_avail[0].setString("Liczba Rekordow");
	display_avail[0].setPosition(sf::Vector2f(width * 0.4, height / (MAX_MENU_ITEMS + 1) * 1));
	display_avail[1].setFillColor(sf::Color::White);
	display_avail[1].setFont(font);
	display_avail[1].setPosition(sf::Vector2f(width * 0.4, height / (MAX_MENU_ITEMS + 1) *1.3));
}
DeletionMenu::~DeletionMenu()
{

}
void DeletionMenu::update_amount(std::string amount_of_records) {
	display_avail[1].setString(amount_of_records);
}
void DeletionMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		window.draw(text[i]);
	}
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		window.draw(display_avail[i]);
	}
}
void DeletionMenu::MoveUp() {
	if (ItemIndex - 1 >= 0)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex--;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}
void DeletionMenu::MoveDown() {
	if (ItemIndex + 1 < MAX_MENU_ITEMS)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex++;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}int DeletionMenu::GetPressedItem() {
	return ItemIndex;
}

