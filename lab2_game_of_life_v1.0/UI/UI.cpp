#include "UI.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

UI::UI()
{
	int born_rule1 = 3;
	int born_rule2 = 3;
	int survival_rule1 = 2;
	int survival_rule2 = 1;
	string name = "";
}

UI::UI(int n, int f) : field(n, f)
{
	int born_rule1 = 3;
	int born_rule2 = 3;
	int survival_rule1 = 2;
	int survival_rule2 = 1;
	string name = "";
}

UI::~UI()
{
	int born_rule1 = 0;
	int born_rule2 = 0;
	int survival_rule1 = 0;
	int survival_rule2 = 0;
	string name = "";
}

void UI::parcer(ifstream & f)
{
	string line;
	getline(f, line);
	if (line != "#Life 1.06")
	{
		cout << "Формат поданного файла неверный." << endl;
	}
	else
	{
		getline(f, line);
	}

	int i = 0;
	string s1 = "";
	string s2 = "";
	for (i = 0; (i < line.size()) && (line[i] != ' '); ++i)
	{
		s1 += line[i];
	}
	for (++i; (i < line.size()) && (line[i] != ' '); ++i)
	{
		s2 += line[i];
	}
	if (s1 != "#N")
	{
		cout << "Отсутствует имя вселенной." << endl;
	}
	else
	{
		this->name = s2;
		getline(f, line);
	}

	int ch = 0;
	i = 0;
	s1 = "";
	s2 = "";
	for (i = 0; (i < line.size()) && (line[i] != ' '); ++i)
	{
		s1 += line[i];
	}
	for (++i; (i < line.size()) && (line[i] != ' '); ++i)
	{
		s2 += line[i];
	}
	if ((s1 != "#R") || (s2 == ""))
	{
		cout << "Отсутствует правило рождения и выживания. Применяются правила по умолчанию: 3 и 2-3." << endl;
		ch = 1;
	}
	else
	{
		this->born_rule1 = 9;
		this->born_rule2 = -1;
		this->survival_rule1 = 9;
		this->survival_rule2 = -1;
		if (s2[0] == 'R')
		{
			for (i = 1; (s2[i] >= '0') && (s2[i] <= '8'); ++i)
			{
				born_rule1 = min(this->born_rule1, s2[i] - '0');
				born_rule1 = max(this->born_rule2, s2[i] - '0');
			}

			if (s2[i] != '/')
			{
				cout << "Неправильный разделитель между правилом рождения и выживания" << endl;
			}
			for (++i; (s2[i] >= '0') && (s2[i] <= '8'); ++i)
			{
				born_rule1 = min(this->survival_rule1, s2[i] - '0');
				born_rule1 = max(this->survival_rule2, s2[i] - '0');
			}
		}
		else
		{
			cout << "Ошибка в задании правила рождения и выживания. Применяются правила по умолчанию: 3 и 2-3." << endl;
			ch = 1;
		}
	}

	if (ch == 1)
	{
		this->born_rule1 = 3;
		this->born_rule2 = 3;
		this->survival_rule1 = 2;
		this->survival_rule2 = 3;
	}
	else
	{
		getline(f, line);
	}

	int x;
	int y;
	do
	{
		s1 = "";
		s2 = "";
		ch = 0;
		for (i = 0; (i < line.size()) && (line[i] != ' '); ++i)	//добавь проверку на циферки
		{
			if ((line[i] >= '0') && (line[i] <= '9'))
			{
				s1 += line[i];
			}
			else
			{
				cout << "Неправильно указаны координаты в файле" << endl;
				ch = 1;
			}

			if (i > 12)
			{
				cout << "Неправильно указаны координаты в файле" << endl;
				ch = 1;
			}
		}
		for (++i; (i < line.size()) && (line[i] != ' '); ++i)	//добавь проверку на циферки
		{
			if ((line[i] >= '0') && (line[i] <= '9'))
			{
				s2 += line[i];
			}
			else
			{
				cout << "Неправильно указаны координаты в файле" << endl;
				ch = 1;
			}

			if (i > 12)
			{
				cout << "Неправильно указаны координаты в файле" << endl;
				ch = 1;
			}
		}

		if ((s1 != "")|| (s2 != ""))
		{
			x = stoi(s1);
			y = stoi(s2);
			this->square_[x * this->N_ + y] = 1;
		}
		else
		{
			cout << "Неправильно указаны координаты в файле" << endl;
			ch = 1;
		}
		
		
	} while (getline(f, line));
}