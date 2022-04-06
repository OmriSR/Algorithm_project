#pragma once
#include <iostream>
#include <stdlib.h>
#include <algorithm>
class inputhandler
{
	int input;
public:
	int operator()()
	{
		std::string str;
		std::cin >> str;
		bool are_digits = std::all_of(str[0]=='-'? str.begin()+1 : str.begin(), str.end(), [](char c) { return isdigit(static_cast<unsigned char>(c)); });
		if (!are_digits)
		{
			system("cls");
			cout << "invalid input" << endl;
			exit(1);
		}
		return atoi(str.c_str());		
	}
	friend std::ostream& operator<<(std::ostream& os, const inputhandler& me);
};

ostream& operator<<(ostream& os, const inputhandler& me)
{
	os << me.input;
	return os;
}

