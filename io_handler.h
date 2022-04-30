#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <algorithm>


using namespace std;



class outputhandler
{
	static ofstream output_file;
public:
	static void openfile_towrite(string input_path)
	{
		if (output_file.is_open()) output_file.close();

		output_file.open(input_path, ios::out);
		if (output_file.is_open() == false) exit_with_a_message("error:input file cannot be open - (path error/system error)");
	}
	static	void closefile()
	{
		output_file.close();
	}
	void operator()(string message)//writes a line to file and console
	{
		cout << message << endl;
		if (!output_file.is_open()) exit_with_a_message("error:trying to write to a closed file");
		output_file << message << endl;
	}
	static void exit_with_a_message(string message)
	{
		system("cls");
		cout << message<<endl;
		system("pause");
		exit(1);
	}
};


class inputhandler
{
	static ifstream input_file;

public:
	static void openfile_toread(string input_path)
	{
		if (input_file.is_open()) input_file.close();

		input_file.open(input_path, ios::in);
		if (input_file.is_open() == false) outputhandler::exit_with_a_message("error:nput file cannot be open - (path error/system error)");
	}
    static	void closefile()
	{
		input_file.close();
	}
	int operator()()//read a line from file
	{
		if (input_file.eof()) outputhandler::exit_with_a_message("error: expected data missing in file or file is corrupted");
		
		std::string str;
	
		input_file >> str;
		
		bool are_digits = std::all_of(str[0]=='-'? str.begin()+1 : str.begin(), str.end(), [](char c) { return isdigit(static_cast<unsigned char>(c)); });

		if (!are_digits) outputhandler::exit_with_a_message("invalid input");
		
		if (str == to_string(LONG_MAX)) str[9] = '6'; //maxval reserved for "infinity"

		return atoi(str.c_str());		
	}
	static bool isEOF() { return input_file.eof(); }
};


