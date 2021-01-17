#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("CreamySunset.ttf")) font.loadFromFile("C:\Windows\Fonts\Arial.ttf");//Case font is not found, use windows arial font
	//Initialize text fields
	text[0].setFillColor(sf::Color::Green);
	text[0].setFont(font);
	text[0].setString("Odczytaj Baze");
	text[0].setPosition(sf::Vector2f(width / 2, height / (MAX_MENU_ITEMS +1) * 1));
	
	text[1].setFillColor(sf::Color::White);
	text[1].setFont(font);
	text[1].setString("Zapisz do bazy");
	text[1].setPosition(sf::Vector2f(width / 2, height / (MAX_MENU_ITEMS + 1) * 2));

	text[2].setFillColor(sf::Color::White);
	text[2].setFont(font);
	text[2].setString("Usun z bazy");
	text[2].setPosition(sf::Vector2f(width / 2, height / (MAX_MENU_ITEMS + 1) * 3));

	text[3].setFillColor(sf::Color::White);
	text[3].setFont(font);
	text[3].setString("Wyjdz");
	text[3].setPosition(sf::Vector2f(width / 2, height / (MAX_MENU_ITEMS + 1) * 4));
	ItemIndex = 0;
}


MainMenu::~MainMenu()
{

}

void MainMenu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		window.draw(text[i]);
	}

}
void MainMenu::MoveUp() {
	if (ItemIndex - 1 >= 0)
	{
		ItemIndex--;
		text[ItemIndex+1].setFillColor(sf::Color::White);
		
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}
void MainMenu::MoveDown() {
	if (ItemIndex + 1 < MAX_MENU_ITEMS)
	{
		ItemIndex++;
		text[ItemIndex-1].setFillColor(sf::Color::White);
		
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}int MainMenu::GetPressedItem() {
	return ItemIndex;
}