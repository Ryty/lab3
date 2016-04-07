#include "Slav.h"

#include <fstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); //leniwa inicializacja
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

_gender Slav::gender()
{
	if(_name[_name.size()-1] == 'a') 
		return female;
	else
		return male;
}
