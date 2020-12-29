#pragma once
#include "SFML/Graphics.hpp"
#include "Textbox.cpp"
#define MAX_MENU_ITEMS 3
class AdditionMenu
{

public:
	AdditionMenu(float width, float height);
	~AdditionMenu();

	

	
	
	Textbox imie{ 20, sf::Color::White, false };
	Textbox nazwisko{ 20, sf::Color::White, false };
	Textbox PESEL{ 20, sf::Color::White, false };
	Textbox wiek{ 20, sf::Color::White, false };
	Textbox bomble{ 20, sf::Color::White, false };
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void SwitchToInput();
	void SwitchBack();
	void MoveUpSecondRow();
	void MoveDownSecondRow();
	int GetSecondRowIndex();
private:
	int ItemIndex;
	int SecondRowIndex;
	sf::Font font;
	sf::Text text[MAX_MENU_ITEMS];
	sf::Text description[5];
};
