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
#include "SimpleDB.cpp"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


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
	while (window.isOpen()) {
		if (fs == MAIN_MENU) {
			window.display();
			//event loop, will keep repeating until there is a relevant event.
			while (window.pollEvent(event)) {
				//This part will be largely the same for most basic menu functionality, based on event type a certain action shall be taken , example, Down key is pressed, call MoveDown, display changes
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
	
			
