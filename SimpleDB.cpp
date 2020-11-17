#include <iostream>
#include<vector>
#include<stdlib.h>
#include <string>
#include<fstream>
#include <conio.h>


using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


class SimpleDB
{
private:
	
	
	struct Dane_pola {
		int wiek;
		string PESEL;
		string imie;
		string nazwisko;
		int liczba_500_plus;
		
	};
	vector<Dane_pola> DB_in_prog;
	
public:

	void Read_DB() {
		int input;
		cout << "Popatrz synek, masz sobie tyle rekordow do wybrania, ktory chcesz zobaczyc (wybierz liczbę mniejszą lub równą od wyświetlonej i nacisnij enter)?" << endl;
		cout << DB_in_prog.size() << endl;
		cin >> input;
	
		auto it = DB_in_prog[input - 1];
		cout << "Pokazuję rekord...." << endl;
		cout << "1- wiek, 2- pesel, 3-imie, 4-nazwisko, 5-wszystko, 6- nie chcę już nic wypisywać, zabierz mnie stąd :c" << endl;
		cin >> input;
		switch (input) {
		case 1:
			cout << it.wiek << endl;
			break;
		case 2:
			cout << it.PESEL << endl;
			break;
		case 3:
			cout << it.imie << endl;
			break;
		case 4:
			cout << it.nazwisko << endl;
			break;
		case 5:	
			cout << it.liczba_500_plus << endl;
			break;
		case 6:
			break;
		default:
			cout << it.wiek << endl;
			cout << it.PESEL << endl;
			cout << it.imie << endl;
			cout << it.nazwisko << endl;
			cout << it.liczba_500_plus << endl;
		}
	};
	void Write_Data() {
		cout << "Podaj wiek" << endl;
		Dane_pola present_struct;
		cin >> present_struct.wiek;
		cout << "Podaj 11-cyfrowy PESEL" << endl;
		cin >> present_struct.PESEL;
		cout << "Podaj imie delikwenta" << endl;
		cin >> present_struct.imie;
		cout << "Podaj też jego nazwisko" << endl;
		cin >> present_struct.nazwisko;
		cout << "Podaj tez liczbe bombelkow 500+" << endl;
		cin >> present_struct.liczba_500_plus;
		cout << "Przetwarzam dane, proszę czekać...." << endl;
		DB_in_prog.push_back(present_struct);
	};
	void Delete(int field_num) {
	};
	
	vector<struct Dane_pola> Search(string) {

	};

};

//SimpleDB::SimpleDB()
//{
//}

//SimpleDB::~SimpleDB()
//{
//}
int main() {
	SimpleDB DB;
	DB.Write_Data();
	DB.Read_DB();
	DB.Write_Data();
	DB.Read_DB();

	return 0;
}