#pragma once
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;
class inputhandler
{
public:
	int operator()()
	{
		std::string str;
		std::cin >> str;
		bool are_digits = std::all_of(str[0]=='-'? str.begin()+1 : str.begin(), str.end(), [](char c) { return isdigit(static_cast<unsigned char>(c)); });
		if (!are_digits)
		{
			system("cls");
			std::cout << "invalid input" << endl;
			exit(1);
		}
		return atoi(str.c_str());		
	}

};


