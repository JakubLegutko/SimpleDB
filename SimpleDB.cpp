#pragma once
#include <iostream>
#include<vector>
#include<stdlib.h>
#include <string>
#include<fstream>
#include <conio.h>
#include <Windows.h>
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

	void Read_DB(int input_choose_rec, string& imie, string& nazwisko, string& pesel, string& wiek, string& bomble) {

		cout << "Popatrz synek, masz sobie tyle rekordow do wybrania, ktory chcesz zobaczyc (wybierz liczbe mniejsza lub rowna od wyœwietlonej i nacisnij enter) lub wcisnij 0 zeby wyjsc?" << endl;
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
	void Write_Data(string imie, string nazwisko, string PESEL, string wiek, string bomble) {
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

		std::fstream read_file("DB.txt");
		//check if file has any record inside - checks if there is any line present except for eof character
		if (!(read_file.peek() == std::ifstream::traits_type::eof()))
		{



			while (!read_file.eof()) {

				Dane_pola td;
				string temp_num;
				string temp_500_pl;
				string temp_imie;
				string temp_nazw;
				string temp_pes;
				//Read 5 lines - a single record
				std::getline(read_file, temp_imie);


				std::getline(read_file, temp_nazw);


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