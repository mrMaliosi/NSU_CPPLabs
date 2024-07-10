#include "parser.h"
#include "ErrorsHierarchy.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <sstream>

using namespace std;

Parser::Parser(std::istream &input_file)
{
	string s;
	getline(input_file, s);
	int l = s.size();
	string word = "";
	if (l > 1000)
	{
		throw LargeInputError();
	}
	int i = 0;
	for (i = 0; (i < l) && (s[i] != ' '); ++i)
	{
		word += s[i];
	}

	if (word == "mute")
	{
		data_.code = 1;
		word = "";
		for (++i; (i < l) && (s[i] != ' '); ++i)
		{
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				word += s[i];
			}
			else
			{
				throw WrongInputError();
			}
		}

		data_.data1 = stoi(word);
		word = "";
		for (++i; (i < l) && (s[i] != ' '); ++i)
		{
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				word += s[i];
			}
			else
			{
				throw WrongInputError();
			}
		}
		data_.data2 = stoi(word);
	}
	else if (word == "mix")
	{
		data_.code = 2;
		++i;
		if ((i < l) && (s[i] != '$'))
		{
			throw WrongInputError();
		}

		word = "";
		for (++i; (i < l) && (s[i] != ' '); ++i)
		{
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				word += s[i];
			}
			else
			{
				throw WrongInputError();
			}
		}
		data_.data1 = stoi(word);
		word = "";
		for (++i; (i < l) && (s[i] != ' '); ++i)
		{
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				word += s[i];
			}
			else
			{
				throw WrongInputError();
			}
		}
		data_.data2 = stoi(word);
	}
	else if (word == "inverse")
	{
		data_.code = 3;
		word = "";
		for (++i; (i < l) && (s[i] != ' '); ++i)
		{
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				word += s[i];
			}
			else
			{
				throw WrongInputError();
			}
		}

		data_.data1 = stoi(word);
		word = "";
		for (++i; (i < l) && (s[i] != ' '); ++i)
		{
			if ((s[i] >= '0') && (s[i] <= '9'))
			{
				word += s[i];
			}
			else
			{
				throw WrongInputError();
			}
		}
		data_.data2 = stoi(word);
	}
	else
	{
		throw WrongInputError();
	}
}

Parser::~Parser()
{
	
}
