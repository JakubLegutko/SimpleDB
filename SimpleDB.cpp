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
#include "Textbox.cpp"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class SimpleDB
{


public:
	struct Dane_pola {
		string wiek;
		string PESEL;
		string imie;
		string nazwisko;
		string liczba_500_plus;

	};

	
	int Get_amount_of_records() {
		return DB_in_prog.size();
	}
	void Read_DB(int input_choose_rec, string &wiek, string &pesel, string &imie, string &nazwisko, string &bomble) {
		
		cout << "Popatrz synek, masz sobie tyle rekordow do wybrania, ktory chcesz zobaczyc (wybierz liczbe mniejsza lub rowna od wyświetlonej i nacisnij enter) lub wcisnij 0 zeby wyjsc?" << endl;
		cout << DB_in_prog.size() << endl;
		
		while (cin.fail() || input_choose_rec > DB_in_prog.size() || input_choose_rec < 0) {
			std::cout << "Error - no such record" << std::endl;
			return;
			
		}
		if (input_choose_rec == 0) {
			return;
		}

		auto it = DB_in_prog[input_choose_rec - 1];
		input_choose_rec = 0;
		cout << "Pokazuje rekord...." << endl;
		
		wiek = it.wiek;
		pesel = it.PESEL;
		imie = it.imie;
		nazwisko = it.nazwisko;
		bomble = it.liczba_500_plus;
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
			/*break;
		case 7:

			break;*/
		//}
			
	};
	void Write_Data(string wiek, string PESEL, string imie, string nazwisko, string bomble) {
		Dane_pola present_struct;
		cout << "Podaj wiek" << endl;
		 present_struct.wiek = wiek;
		cout << "Podaj 11-cyfrowy PESEL" << endl;
		present_struct.PESEL = PESEL;
		cout << "Podaj imie delikwenta" << endl;
		present_struct.imie = imie;
		cout << "Podaj tez jego nazwisko" << endl;
		present_struct.nazwisko = nazwisko;
		cout << "Podaj tez liczbe bombelkow 500+" << endl;
		present_struct.liczba_500_plus = bomble;
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
			cout << '\n';

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
	void Delete(int field_num) {
		
		cout << "ktory rekord chcesz wywalic? (polecam najpierw sprawdzic ich zawartosc coby niespodzianek nie bylo!" << endl;
		if (!(field_num > DB_in_prog.size() || field_num < 0))
			DB_in_prog.erase(DB_in_prog.begin() + field_num - 1);
		else cout << "No such record!" << endl;
	};

	vector<struct Dane_pola> Search(string) {

	};
	private:


		vector<Dane_pola> DB_in_prog;
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
	string amount_of_records;
	enum fsm {
		MAIN_MENU,
		DISPLAY_MENU,
		ADD_MENU,
		DELETE_MENU
	};
	fsm fs = MAIN_MENU;
	sf::RenderWindow window{ sf::VideoMode{800, 600}, "PiSOS v.21.37" };
	sf::Event event;


	MainMenu mainmenu(window.getSize().x, window.getSize().y);

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
							amount_of_records = std::to_string(DB.Get_amount_of_records());
							cout << amount_of_records;

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
			DBDisplayMenu displaymenu(window.getSize().x, window.getSize().y);
		
			amount_of_records = std::to_string(DB.Get_amount_of_records());
			int record_to_display;
			bool been_in_choice = false;
			displaymenu.update_amount(amount_of_records);
			while (fs == DISPLAY_MENU) {
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
								cout << "0. button in displaymenu" << endl;
								if (been_in_choice) {
									string wiek;
									string PESEL;
									string imie;
									string nazwisko;
									string bomble;
							
									DB.Read_DB(record_to_display,wiek,PESEL,imie,nazwisko,bomble);
									displaymenu.display[0].setString(imie);
									displaymenu.display[1].setString(nazwisko);
									displaymenu.display[2].setString(PESEL);
									displaymenu.display[3].setString(wiek);
									displaymenu.display[4].setString(bomble);
									been_in_choice = false;
									window.clear();
									
									displaymenu.wybor.drawTo(window);
									displaymenu.draw(window);
									window.display();
								}
								else {
									cout << "Choice not made yet" << endl;
								}
								break;
							case 1:
								cout << "1. button in displaymenu" << endl;
								//DB.Read_DB();
								//break;
							
								displaymenu.wybor.setSelected(true);
								displaymenu.wybor.drawTo(window);
								window.display();
								
								while (displaymenu.wybor.getSelection()) {
							
									while (window.pollEvent(event))
									{
										switch (event.type) {
										case sf::Event::TextEntered:
											window.clear();
											displaymenu.wybor.typedOn(event);
											displaymenu.draw(window);
											displaymenu.wybor.drawTo(window);
											window.display();
										case sf::Event::KeyReleased:
											if (event.key.code == sf::Keyboard::End) {

												displaymenu.wybor.setSelected(false);
												
												if (!(displaymenu.wybor.getText() == "")) record_to_display = std::stoi(displaymenu.wybor.getText());
												else record_to_display = 0;
												
												been_in_choice = true;
											}
										}
									}
								}
								break;
							case 2:

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
				displaymenu.wybor.drawTo(window);
			}
		}

		if (fs == ADD_MENU) {
			AdditionMenu addmenu(window.getSize().x, window.getSize().y);
			
			out_of_loop:
			while (fs == ADD_MENU) {
				window.clear();

				addmenu.draw(window);
				addmenu.imie.drawTo(window);
				addmenu.nazwisko.drawTo(window);
				addmenu.PESEL.drawTo(window);
				addmenu.wiek.drawTo(window);
				addmenu.bomble.drawTo(window);
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
							case 2:
								cout << "2. button" << endl;
								fs = MAIN_MENU;

								break;
							case 1:
								cout << "Zapis" << endl;
								DB.Write_Data(addmenu.imie.getText(),
									addmenu.nazwisko.getText(),
									addmenu.PESEL.getText(),
									addmenu.wiek.getText(),
									addmenu.bomble.getText());
								fs = MAIN_MENU;
								break;
							case 0:
								cout << "1. button in displaymenu" << endl;
								addmenu.SwitchToInput();
								window.clear();
								addmenu.draw(window);
								window.display();
								
								while (1) {
									window.clear();
									addmenu.draw(window);
									addmenu.imie.drawTo(window);
									addmenu.nazwisko.drawTo(window);
									addmenu.PESEL.drawTo(window);
									addmenu.wiek.drawTo(window);
									addmenu.bomble.drawTo(window);
									window.display();
									while(window.pollEvent(event)){
									window.clear();
									addmenu.draw(window);
									window.display();
									switch (event.type) {
									case sf::Event::KeyReleased:
										switch (event.key.code)
										{
										case sf::Keyboard::Up:
											addmenu.MoveUpSecondRow();
											break;

										case sf::Keyboard::Down:
											addmenu.MoveDownSecondRow();
											break;
										case sf::Keyboard::Escape:
											addmenu.SwitchBack();
											goto out_of_loop;
										case sf::Keyboard::Return:
											switch (addmenu.GetSecondRowIndex())
											{

											case 0:
												addmenu.imie.setSelected(true);
												addmenu.imie.drawTo(window);
												window.display();
												while (addmenu.imie.getSelection()) {
													while (window.pollEvent(event))
													{
														switch (event.type) {
														case sf::Event::TextEntered:
															addmenu.imie.typedOn(event);
															window.clear();
															addmenu.imie.drawTo(window);
															addmenu.nazwisko.drawTo(window);
															addmenu.PESEL.drawTo(window);
															addmenu.wiek.drawTo(window);
															addmenu.bomble.drawTo(window);
															addmenu.draw(window);
															window.display();
														case sf::Event::KeyReleased:
															if (event.key.code == sf::Keyboard::End) {

																addmenu.imie.setSelected(false);
															}
														}
													}
												}
												break;
											case 1:
												addmenu.nazwisko.setSelected(true);
												addmenu.nazwisko.drawTo(window);
												window.display();
												while (addmenu.nazwisko.getSelection()) {
													while (window.pollEvent(event))
													{
														switch (event.type) {
														case sf::Event::TextEntered:
															addmenu.nazwisko.typedOn(event);
															window.clear();
															addmenu.imie.drawTo(window);
															addmenu.nazwisko.drawTo(window);
															addmenu.PESEL.drawTo(window);
															addmenu.wiek.drawTo(window);
															addmenu.bomble.drawTo(window);
															addmenu.draw(window);
															window.display();
														case sf::Event::KeyReleased:
															if (event.key.code == sf::Keyboard::End) {

																addmenu.nazwisko.setSelected(false);
															}
														}
													}
												}
												break;
											case 2:
												addmenu.PESEL.setSelected(true);
												addmenu.PESEL.drawTo(window);
												window.display();
												while (addmenu.PESEL.getSelection()) {
													while (window.pollEvent(event))
													{
														switch (event.type) {
														case sf::Event::TextEntered:
															addmenu.PESEL.typedOn(event);
															window.clear();
															addmenu.imie.drawTo(window);
															addmenu.nazwisko.drawTo(window);
															addmenu.PESEL.drawTo(window);
															addmenu.wiek.drawTo(window);
															addmenu.bomble.drawTo(window);
															addmenu.draw(window);
															window.display();
														case sf::Event::KeyReleased:
															if (event.key.code == sf::Keyboard::End) {

																addmenu.PESEL.setSelected(false);
															}
														}
													}
												}
												break;
											case 3:
												addmenu.wiek.setSelected(true);
												addmenu.wiek.drawTo(window);
												window.display();
												while (addmenu.wiek.getSelection()) {
													while (window.pollEvent(event))
													{
														switch (event.type) {
														case sf::Event::TextEntered:
															addmenu.wiek.typedOn(event);
															window.clear();
															addmenu.imie.drawTo(window);
															addmenu.nazwisko.drawTo(window);
															addmenu.PESEL.drawTo(window);
															addmenu.wiek.drawTo(window);
															addmenu.bomble.drawTo(window);
															addmenu.draw(window);
															window.display();
														case sf::Event::KeyReleased:
															if (event.key.code == sf::Keyboard::End) {

																addmenu.wiek.setSelected(false);
															}
														}
													}
												}
												break;
											case 4:
												addmenu.bomble.setSelected(true);
												addmenu.bomble.drawTo(window);
												window.display();
												while (addmenu.bomble.getSelection()) {
													while (window.pollEvent(event))
													{
														switch (event.type) {
														case sf::Event::TextEntered:
															addmenu.bomble.typedOn(event);
															window.clear();
															addmenu.imie.drawTo(window);
															addmenu.nazwisko.drawTo(window);
															addmenu.PESEL.drawTo(window);
															addmenu.wiek.drawTo(window);
															addmenu.bomble.drawTo(window);
															addmenu.draw(window);
															window.display();
														case sf::Event::KeyReleased:
															if (event.key.code == sf::Keyboard::End) {

																addmenu.bomble.setSelected(false);
															}
														}
													}
												}
											}
												
											}
										}
										
										


									}

								}

							}

							

						}
					}
					
				}
			}
		}
				if (fs == DELETE_MENU) {
					DeletionMenu deletemenu(window.getSize().x, window.getSize().y);
					deletemenu.update_amount(amount_of_records);
					while (fs == DELETE_MENU) {
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
										if (DB.Get_amount_of_records() > 0) {

											DB.Delete(1);
										}
										else cout << "Nothing to delete" << endl;
										amount_of_records = std::to_string(DB.Get_amount_of_records());
										deletemenu.update_amount(amount_of_records);
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
			}
			return 0;
		}
	
			
