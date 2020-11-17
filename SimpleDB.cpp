#include <iostream>
#include<vector>
#include<stdlib.h>

using std::vector;




class SimpleDB
{
public:
	SimpleDB();
	~SimpleDB();
	char Read(FILE) {
	};
	vector<char> Write(FILE) {
	};
	vector<char> Delete(FILE, int field_num) {
	};
private:

};

SimpleDB::SimpleDB()
{
}

SimpleDB::~SimpleDB()
{
}
