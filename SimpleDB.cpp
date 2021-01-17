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


	
	int Get_amount_of_records() {
		return DB_in_prog.size();
	}
	
	void Read_DB(int input_choose_rec, string &imie, string &nazwisko, string &pesel, string &wiek, string &bomble) {
		
		cout << "Popatrz synek, masz sobie tyle rekordow do wybrania, ktory chcesz zobaczyc (wybierz liczbe mniejsza lub rowna od wyświetlonej i nacisnij enter) lub wcisnij 0 zeby wyjsc?" << endl;
		cout << DB_in_prog.size() << endl;
		//check if record number argument is valid - if not, stop the function
		while (input_choose_rec > DB_in_prog.size() || input_choose_rec < 0) {
			std::cout << "Error - no such record" << std::endl;
			return;
			
		}
		//The records are numbered from 1, thus stop if function got 0 as record number argument
		if (input_choose_rec == 0) {
			return;
		}
		//Initialize temporary record to store the read values for displaying
		auto it = DB_in_prog[input_choose_rec - 1];
		cout << "Pokazuje rekord...." << endl;
		//put the values of the temporary record into variables given by reference to the function
		imie = it.imie;
		nazwisko = it.nazwisko;
		wiek = it.wiek;
		pesel = it.PESEL;
		bomble = it.liczba_500_plus;
			cout << "imie: ";
			cout << it.imie << endl;
			cout << "nazwisko: ";
			cout << it.nazwisko << endl;
			cout << "PESEL: ";
			cout << it.PESEL << endl;
			cout << "wiek: ";
			cout << it.wiek << endl;
			cout << "liczba bombelkow: ";
			cout << it.liczba_500_plus << endl;
		
			
	};
	void Write_Data(string imie , string nazwisko, string PESEL, string wiek, string bomble) {
		// Create temporary structure to store values, then fill it with input arguments
		Dane_pola present_struct;
		cout << "Podaj imie delikwenta" << endl;
		 present_struct.imie = imie;
		cout << "Podaj tez jego nazwisko" << endl;
		present_struct.nazwisko = nazwisko;
		cout << "Podaj 11-cyfrowy PESEL" << endl;
		present_struct.PESEL = PESEL;
		cout << "Podaj wiek" << endl;
		present_struct.wiek = wiek;
		cout << "Podaj tez liczbe bombelkow 500+" << endl;
		present_struct.liczba_500_plus = bomble;
		cout << "Przetwarzam dane, prosze czekac...." << endl;
		//Store the struct values onto the vector used as memory
		DB_in_prog.push_back(present_struct);
		Sleep(1000);
		cout << "Zapisano!" << endl;
	};
	void Init() {
		
		cout << "Witaj w nowym systemie informatycznym, sluzacemu jako baza danych potencjalnych wyborcow!" << endl;
		cout << "System zostal przyrzadzony przez najlepszych informatykow, wiec baza za kazdym wlaczeniem zmienia kolejnosc rekordow" << endl;
		
		cout << "Rekordu nie trzeba uzupelniac do konca, ale bombelki musza byc!!!" << endl;
		//open stream to file to read later
		std::fstream read_file("DB.txt");
		//check if file exists
		if (!(read_file.peek() == std::ifstream::traits_type::eof()))
		{


			//Loop read the file as long as there's data to be read
			while (!read_file.eof()) {
				//Create temporary struct to store read data
				Dane_pola td;
				string temp_num;
				string temp_500_pl;
				string temp_imie;
				string temp_nazw;
				string temp_pes;
				//Read 5 lines - a single record
				std::getline(read_file, temp_imie);


				std::getline(read_file, temp_nazw );


				std::getline(read_file, temp_pes);


				std::getline(read_file, temp_num);

				std::getline(read_file, temp_500_pl);
				//store the values inside the previously created struct
				td.imie = temp_imie;
				td.nazwisko = temp_nazw;
				td.PESEL = temp_pes;
				td.wiek = temp_num;
				td.liczba_500_plus = temp_500_pl;
				if (!(temp_500_pl == ""))
					//Push to vector if last data field is not empty, else drop the record, this is implemented to stop empty records from appearing upon startup, this is intended!
					//Another way of implementing this could be a hidden field placed on the last spot which would be filled with data only if any other field in the record was filled.
					DB_in_prog.push_back(td);

			}
		}
		//Close the file stream and remove the txt file, new one will be created at shutdown.
		read_file.close();
		if (remove("DB.txt") != 0)
			perror("File deletion failed");
		else
			cout << '\n';

	}

	void Save_Exit() {
		//Create new DB file by opening output file stream
		std::ofstream out_file;
		out_file.open("DB.txt");
		while (DB_in_prog.size()) {
			//Take last record into temporary struct, remove it from memory vector, this will result in reversal of records upon next launch and is also intended.
			//Placing the values from the start of the vector or reversing read function would make the records appear in the placement order, however this is more fun, and this DB should be fun (not for the user though).
			Dane_pola it = DB_in_prog.back();
			out_file << it.imie << endl;
			out_file << it.nazwisko << endl;
			out_file << it.PESEL << endl;
			out_file << it.wiek << endl;
			out_file << it.liczba_500_plus << endl;

			DB_in_prog.pop_back();
		}
		//Close file stream and kill program
		out_file.close();
		exit(0);
	}
	void Delete(int field_num) {
		
		cout << "ktory rekord chcesz wywalic? (polecam najpierw sprawdzic ich zawartosc coby niespodzianek nie bylo!" << endl;
		//Check if record can be deleted by comparing vector length with input argument, at the moment there is no way to choose deleted vector since I'm passing 1 as an argument anyway, but implementation is possible.
		if (!(field_num > DB_in_prog.size() || field_num < 0))
			DB_in_prog.erase(DB_in_prog.begin() + field_num - 1);
		else cout << "No such record!" << endl;
	};

	
	private:

		//This struct works as a record.
		struct Dane_pola {
			string wiek;
			string PESEL;
			string imie;
			string nazwisko;
			string liczba_500_plus;

		};
		//This vector acts as memory for the database, it takes the above structs as data.
		vector<Dane_pola> DB_in_prog;
};
//function used to verify if input index is digits only to prevent errors with string to int conversion
bool is_digits(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit); 
}
int main() {
	//Call Init to read potential records from file and set up the DB.
	SimpleDB DB;
	DB.Init();
	//This is used in various places in the program to dynamically update amount of records available
	string amount_of_records;
	//Finite State Machine used to navigate between menus - upon change a different menu is rendered onto the window
	enum fsm {
		MAIN_MENU,
		DISPLAY_MENU,
		ADD_MENU,
		DELETE_MENU
	};
	fsm fs = MAIN_MENU;
	//Create window and initialize event queue
	sf::RenderWindow window{ sf::VideoMode{800, 600}, "OSSiP v.0.37" };
	sf::Event event;
	
	//Render main menu onto the screen
	MainMenu mainmenu(window.getSize().x, window.getSize().y);
	//initialize program loop - as long as window remains open the program won't shut down
	while (window.isOpen()) {
		if (fs == MAIN_MENU) {
			window.display();
			//event loop, will keep repeating until there is a relevant event.
			while (window.pollEvent(event)) {
				//This part will be largely the same for most basic menu functionality, based on event type a certain action shall be taken , example, Down key is pressed, call MoveDown, display
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
							cout << "1. button MainMenu-Display" << endl;
							fs = DISPLAY_MENU;
							cout << fs;
							break;
						case 1:
							cout << "2. button MainMenu-Add" << endl;
							fs = ADD_MENU;
							break;
						case 2:
							cout << "3. button MainMenu-Delete" << endl;
							fs = DELETE_MENU;
							amount_of_records = std::to_string(DB.Get_amount_of_records());
							cout << amount_of_records;

							break;
						case 3:
							cout << "4. button MainMenu -Exit" << endl;
							window.close();
							DB.Save_Exit();
							break;
						}
						break;
					}



				}

			}
			//every time the second loop has been left clear the screen and push new data to be displayed with window.display() above the loop, this will only trigger if there is a change to be drawn, because of the second loop's design
			window.clear();
			mainmenu.draw(window);
		}


		if (fs == DISPLAY_MENU) {
			DBDisplayMenu displaymenu(window.getSize().x, window.getSize().y);
		
			amount_of_records = std::to_string(DB.Get_amount_of_records());
			//This will keep the record number chosen by the user to be displayed
			int record_to_display;
			//Used to check if a choice has been made (if user put new data in, or even just entered the text field) since last attempt of displaying record
			bool been_in_choice = false;
			//This will refresh amount of available records
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
								cout << "1. button displaymenu-display" << endl;
								//If there is a correct value in record to display, this will display the chosen record in the data fields
								if (been_in_choice) {
									string wiek;
									string PESEL;
									string imie;
									string nazwisko;
									string bomble;
							
									DB.Read_DB(record_to_display,imie,nazwisko,PESEL,wiek,bomble);
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
								cout << "2. button in displaymenu-choose" << endl;
								
							//Trigger text box writing
								displaymenu.wybor.setSelected(true);
								displaymenu.wybor.drawTo(window);
								window.display();
								
								while (displaymenu.wybor.getSelection()) {
								//While in textbox, do a new event loop
									while (window.pollEvent(event))
									{
										switch (event.type) {
										case sf::Event::TextEntered://poll for text entered, display it in the text box
											window.clear();
											displaymenu.wybor.typedOn(event);
											displaymenu.draw(window);
											displaymenu.wybor.drawTo(window);
											window.display();
										case sf::Event::KeyReleased://To exit a text box press End key
											if (event.key.code == sf::Keyboard::End) {
												//Disable text box, keeping the last input
												displaymenu.wybor.setSelected(false);
												
												//Check if there is any data in the text field and if data is digits only, after all this is the record index, it can't be anything else but a number.
												if (!(displaymenu.wybor.getText() == "") && is_digits(displaymenu.wybor.getText())) record_to_display = std::stoi(displaymenu.wybor.getText());
												else { record_to_display = 0; 
												cout << "Record not chosen, either no input or invalid input - numbers only allowed!" << endl;
												}
												
												been_in_choice = true;
											}
										}
									}
								}
								break;
							case 2:

								cout << "3. button in displaymenu-back to main" << endl;
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
			//A little cheat to simplify exiting the gargantuan loops below
			out_of_loop:
			while (fs == ADD_MENU) {
				window.clear();
				//Make sure data the user put in is visible all the time
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
								cout << "3. button in add menu-back to main" << endl;
								fs = MAIN_MENU;

								break;
							case 1:
								cout << "2. button in add menu, save record" << endl;
								DB.Write_Data(addmenu.imie.getText(),
									addmenu.nazwisko.getText(),
									addmenu.PESEL.getText(),
									addmenu.wiek.getText(),
									addmenu.bomble.getText());
								fs = MAIN_MENU;
								break;
							case 0:
								cout << "1. button in add menu-move to add" << endl;
								//Switch to second column, consists of text boxes for the user to place inputs
								addmenu.SwitchToInput();
								window.clear();
								addmenu.draw(window);
								window.display();
								//Only way to exit this loop is the "Cheat" goto from before, tried other methods, failed miserably
								while (1) {
									//Again, make sure everything is displayed all the time
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
											//Based on the currently selected textbox, activate input in it, and display user written data.
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
										//Check if deletion is possible, meaning if index exists in vector
										if (DB.Get_amount_of_records() > 0) {

											DB.Delete(1);
										}
										else cout << "Nothing to delete" << endl;
										amount_of_records = std::to_string(DB.Get_amount_of_records());
										deletemenu.update_amount(amount_of_records);
										break;
									case 1:
										cout << "2. button in deletemenu- back to main" << endl;
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
	
			
