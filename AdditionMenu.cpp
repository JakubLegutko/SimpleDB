#include "AdditionMenu.h"
AdditionMenu::AdditionMenu(float width, float height) {

	if (!font.loadFromFile("CreamySunset.ttf"))
	{
		//handle erorr
	}

	text[0].setFillColor(sf::Color::Green);
	text[0].setFont(font);
	text[0].setString("Uzupelnij Rekord");
	text[0].setPosition(sf::Vector2f(width * 0.7, height / (MAX_MENU_ITEMS + 1) * 1));

	

	text[1].setFillColor(sf::Color::White);
	text[1].setFont(font);
	text[1].setString("Zapisz rekord");
	text[1].setPosition(sf::Vector2f(width * 0.75, height / (MAX_MENU_ITEMS + 1) * 2));
	text[2].setFillColor(sf::Color::White);
	text[2].setFont(font);
	text[2].setString("Wroc do menu glownego");
	text[2].setPosition(sf::Vector2f(width * 0.6, height / (MAX_MENU_ITEMS + 1) * 3));
	ItemIndex = 0;
	SecondRowIndex = 0;
	imie.setPosition({ 150, 100 });
	imie.setLimit(true, 30);
	imie.setFont(font);
	nazwisko.setPosition({ 150, 200 });
	nazwisko.setLimit(true, 30);
	nazwisko.setFont(font);
	PESEL.setPosition({ 150, 300 });
	PESEL.setLimit(true, 11);
	PESEL.setFont(font);
	wiek.setPosition({ 150, 400 });
	wiek.setLimit(true, 3);
	wiek.setFont(font);
	bomble.setPosition({ 150, 500 });
	bomble.setLimit(true, 30);
	bomble.setFont(font);
	description[0].setFillColor(sf::Color::White);
	description[0].setFont(font);
	description[0].setString("Imie");
	description[0].setPosition(sf::Vector2f(150, 75));
	description[1].setFillColor(sf::Color::White);
	description[1].setFont(font);
	description[1].setString("Nazwisko");
	description[1].setPosition(sf::Vector2f(150,175));
	description[2].setFillColor(sf::Color::White);
	description[2].setFont(font);
	description[2].setString("PESEL");
	description[2].setPosition(sf::Vector2f(150,275));
	description[3].setFillColor(sf::Color::White);
	description[3].setFont(font);
	description[3].setString("Wiek");
	description[3].setPosition(sf::Vector2f(150,375));
	description[4].setFillColor(sf::Color::White);
	description[4].setFont(font);
	description[4].setString("Bombelki");
	description[4].setPosition(sf::Vector2f(150,475));
}
AdditionMenu::~AdditionMenu()
{

}
int AdditionMenu::GetSecondRowIndex() {
	return SecondRowIndex;
}
void AdditionMenu::MoveUpSecondRow() {
	if (SecondRowIndex - 1 >= 0)
	{
		description[SecondRowIndex].setFillColor(sf::Color::White);
		SecondRowIndex--;
		description[SecondRowIndex].setFillColor(sf::Color::Green);
	}
}
void AdditionMenu::MoveDownSecondRow() {
	if (SecondRowIndex + 1 < 5)
	{
		description[SecondRowIndex].setFillColor(sf::Color::White);
		SecondRowIndex++;
		description[SecondRowIndex].setFillColor(sf::Color::Green);
	}
}
void AdditionMenu::SwitchBack() {
	text[0].setFillColor(sf::Color::Green);
	description[SecondRowIndex].setFillColor(sf::Color::White);
}
void AdditionMenu::SwitchToInput() {
	text[0].setFillColor(sf::Color::White);
	description[SecondRowIndex].setFillColor(sf::Color::Green);

}

void AdditionMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		window.draw(text[i]);
	}
	for (int i = 0; i <5; i++)
	{
		window.draw(description[i]);
	}
}
void AdditionMenu::MoveUp() {
	if (ItemIndex - 1 >= 0)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex--;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}
void AdditionMenu::MoveDown() {
	if (ItemIndex + 1 < MAX_MENU_ITEMS)
	{
		text[ItemIndex].setFillColor(sf::Color::White);
		ItemIndex++;
		text[ItemIndex].setFillColor(sf::Color::Green);
	}
}
int AdditionMenu::GetPressedItem() {
	return ItemIndex;
}