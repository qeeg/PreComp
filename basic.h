#ifndef BASIC_H
#define BASIC_H

#include <string>

using namespace std;

typedef double number;

struct var
{
	number value;
	bool namevalid;
	string name;

	var();
};

#endif //BASIC_H