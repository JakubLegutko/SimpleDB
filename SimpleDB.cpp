#include <iostream>
#include<vector>
#include<stdlib.h>
#include <string>
#include<fstream>
#include <conio.h>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include "DBDisplayMenu.h"
#include "AdditionMenu.h"
#include "DeletionMenu.h"
#include <Windows.h>
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class SimpleDB
{
private:
	
	
	struct Dane_pola {
		string wiek;
		string PESEL;
		string imie;
		string nazwisko;
		string liczba_500_plus;
		
	};
	vector<Dane_pola> DB_in_prog;
	
public:

	void Read_DB() {
		 int input_choose_rec;
		cout << "Popatrz synek, masz sobie tyle rekordow do wybrania, ktory chcesz zobaczyc (wybierz liczbe mniejsza lub rowna od wyświetlonej i nacisnij enter) lub wcisnij 0 zeby wyjsc?" << endl;
		cout << DB_in_prog.size() << endl;
		cin >> input_choose_rec;
		
		while (cin.fail() || input_choose_rec > DB_in_prog.size() || input_choose_rec < 0) {
			std::cout << "Error" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> input_choose_rec;
		}
		if (input_choose_rec == 0) {
			return;
		}
	
		auto it = DB_in_prog[input_choose_rec - 1];
		input_choose_rec = 0;
		cout << "Pokazuje rekord...." << endl;
		cout << "1- wiek, 2- pesel, 3-imie, 4-nazwisko, 5-bombelki,6 wszystko, 7- nie chce juz nic wypisywac, zabierz mnie stad :c" << endl;
		int input_choose_field;
		cin >> input_choose_field;
		switch (input_choose_field) {
		case 1:
			cout << "wiek: ";
			cout << it.wiek << endl;
			break;
		case 2:
			cout << "PESEL: ";
			cout << it.PESEL << endl;
			break;
		case 3:
			cout << "imie: ";
			cout << it.imie << endl;
			break;
		case 4:
			cout << "nazwisko: ";
			cout << it.nazwisko << endl;
			break;
		case 5:	
			cout << "liczba bombelkow: ";
			cout << it.liczba_500_plus << endl;
			break;
		case 6:
			cout << "wiek: ";
			cout << it.wiek << endl;
			cout << "PESEL: ";
			cout << it.PESEL << endl;
			cout << "imie: ";
			cout << it.imie << endl;
			cout << "nazwisko: ";
			cout << it.nazwisko << endl;
			cout << "liczba bombelkow: ";
			cout << it.liczba_500_plus << endl;
			break;
		case 7:
			
			break;
		}
	};
	void Write_Data() {
		Dane_pola present_struct;
		cout << "Podaj wiek" << endl;
		cin >> present_struct.wiek;
		cout << "Podaj 11-cyfrowy PESEL" << endl;
		cin >> present_struct.PESEL;
		cout << "Podaj imie delikwenta" << endl;
		cin >> present_struct.imie;
		cout << "Podaj tez jego nazwisko" << endl;
		cin >> present_struct.nazwisko;
		cout << "Podaj tez liczbe bombelkow 500+" << endl;
		cin >> present_struct.liczba_500_plus;
		cout << "Przetwarzam dane, prosze czekac...." << endl;
		DB_in_prog.push_back(present_struct);
		Sleep(1000);
		cout << "Zapisano!" << endl;
	};
	void Init() {
		//LOAD DB
		cout << "Witaj w nowym systemie informatycznym Pana Prezesa, PiSOS, sluzacemu jako baza danych potencjalnych wyborcow!" << endl;
		cout << "System zostal przyrzadzony przez najlepszych informatykow, wiec baza za kazdym wlaczeniem zmienia kolejnosc rekordow" << endl;
		cout << "Niechaj chwala bedzie Prezesowi!" << endl;
		
		std::fstream read_file("DB.txt");
		if (!(read_file.peek() == std::ifstream::traits_type::eof()))
		{



			while (!read_file.eof()) {
				Dane_pola td;
				string temp_num;
				string temp_500_pl;
				string temp_imie;
				string temp_nazw;
				string temp_pes;
				std::getline(read_file, temp_num);
					
				
				std::getline(read_file, temp_pes);
				
				
				std::getline(read_file, temp_imie);
					
				
				std::getline(read_file, temp_nazw);
				
				std::getline(read_file, temp_500_pl);
					
				td.wiek = temp_num;
				td.PESEL = temp_pes;
				td.imie = temp_imie;
				td.nazwisko = temp_nazw;
				td.liczba_500_plus = temp_500_pl;
				if (!(temp_500_pl == ""))
					DB_in_prog.push_back(td);

			}
		}
		read_file.close();
		if (remove("DB.txt") != 0)
			perror("File deletion failed");
		else
			cout <<'\n' ;

	}

	void Save_Exit() {
		std::ofstream out_file;
		out_file.open("DB.txt");
		while (DB_in_prog.size()) {
			Dane_pola it = DB_in_prog.back();
			out_file << it.wiek << endl;
			out_file << it.PESEL << endl;
			out_file << it.imie << endl;
			out_file << it.nazwisko << endl;
			out_file << it.liczba_500_plus << endl;

			DB_in_prog.pop_back();
		}
		out_file.close();
		exit(0);
	}
	void Delete() {
		int field_num;
		cout << "ktory rekord chcesz wywalic? (polecam najpierw sprawdzic ich zawartosc coby niespodzianek nie bylo!" << endl;
		cin >> field_num;
		DB_in_prog.erase(DB_in_prog.begin() + field_num-1);
	};
	
	vector<struct Dane_pola> Search(string) {

	};

};

//SimpleDB::SimpleDB()
//{
//}

//SimpleDB::~SimpleDB()
//{
//	}
int main() {
	SimpleDB DB;
	DB.Init();
	enum fsm {
		MAIN_MENU,
		DISPLAY_MENU,
		ADD_MENU,
		DELETE_MENU
	};
	fsm fs = MAIN_MENU;
	sf::RenderWindow window{ sf::VideoMode{800, 600}, "PiSOS v.21.37" };
	sf::Event event;
		DeletionMenu deletemenu(window.getSize().x, window.getSize().y);
		AdditionMenu addmenu(window.getSize().x, window.getSize().y);
		MainMenu mainmenu(window.getSize().x, window.getSize().y);
		DBDisplayMenu displaymenu(window.getSize().x, window.getSize().y);
		while (window.isOpen()) {
			if (fs == MAIN_MENU) {
			window.display();
			while (window.pollEvent(event)) {

				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						mainmenu.MoveUp();
						break;

					case sf::Keyboard::Down:
						mainmenu.MoveDown();
						break;
					case sf::Keyboard::Return:
						switch (mainmenu.GetPressedItem())
						{
						case 0:
							cout << "1. button" << endl;
							fs = DISPLAY_MENU;
							cout << fs;
							break;
						case 1:
							cout << "2. button" << endl;
							fs = ADD_MENU;
							break;
						case 2:
							cout << "3. button" << endl;
							fs = DELETE_MENU;
							break;
						case 3:
							cout << "4. button" << endl;
							window.close();
							DB.Save_Exit();
							break;
						}
						break;
					}



				}

			}	
			
			window.clear();
			mainmenu.draw(window);
		}
		

	if (fs == DISPLAY_MENU) {
		
		
			window.display();
			while (window.pollEvent(event)) {

				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						displaymenu.MoveUp();
						break;

					case sf::Keyboard::Down:
						displaymenu.MoveDown();
						break;
					case sf::Keyboard::Return:
						switch (displaymenu.GetPressedItem())
						{
						case 0:
							cout << "1. button in displaymenu" << endl;
							DB.Read_DB();
							break;
						case 1:
							cout << "2. button" << endl;
							fs = MAIN_MENU;
							break;

						}
						break;
					}



				}

			}
			window.clear();
			displaymenu.draw(window);
		}	
	if (fs == ADD_MENU) {


		window.display();
		while (window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					addmenu.MoveUp();
					break;

				case sf::Keyboard::Down:
					addmenu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (addmenu.GetPressedItem())
					{
					case 0:
						cout << "1. button in displaymenu" << endl;
						DB.Write_Data();
						break;
					case 1:
						cout << "2. button" << endl;
						fs = MAIN_MENU;
						break;

					}
					break;
				}



			}

		}
		window.clear();
		addmenu.draw(window);
	}
	if (fs == DELETE_MENU) {


		window.display();
		while (window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					deletemenu.MoveUp();
					break;

				case sf::Keyboard::Down:
					deletemenu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (deletemenu.GetPressedItem())
					{
					case 0:
						cout << "1. button in deletemenu" << endl;
						DB.Delete();
						break;
					case 1:
						cout << "2. button" << endl;
						fs = MAIN_MENU;
						break;

					}
					break;
				}



			}

		}
		window.clear();
		deletemenu.draw(window);
	}
	
}

	

	return 0;
}