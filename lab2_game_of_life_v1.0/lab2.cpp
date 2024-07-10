#include <iostream>
#include <string>
#include <fstream>
#include "MagicWord/MagicWord.h"
#include "field/field.h"
#include "UI/UI.h"

using namespace std;

//MVC паттерн
int main(int argc, char * argv[])
{
	setlocale(LC_CTYPE, "rus");
	MagicWord w;
	if (argc == 1)			//Случайное поле
	{
		MagicWord s;
		field q(50, 1);
		while (1 > 0)
		{
			cin >> s;
			if (s.code == 1)
			{
				ofstream f(s.s);
				if (f.is_open() == 0)
				{
					cout << "Файл не найден. Возможно, проблема в вас..." << endl;
				}
				else
				{
					string rule = "R3/S23";
					q.dump(f, s.s, rule);
				}
				f.close();
			}
			else if (s.code == 2)
			{
				for (int j = 0; j < s.a; ++j)
				{
					q.next_tick(3, 3, 2, 3);
				}
				q.printer();
			}
			else if (s.code == 3)
			{
				cout << "Серьёзно? Вы хотите убить всю жизнь в этом маленьком мирке?" << endl;
				cout << "Ну что ж, как прикажете..." << endl;
				return 0;
			}
		}
	}
	else if (argc == 2)		//Из входного файла
	{
		MagicWord s;
		UI q(50, 0);
		ifstream in(argv[1]);
		if (in.is_open() == 0)
		{
			cout << "Входной файл не найден. Возможно, неправильно указан путь." << endl;
			return 1;
		}
		q.parcer(in);
        in.close();
		while (1 > 0)
		{
			cin >> s;
			if (s.code == 1)
			{
				ofstream f(s.s);
				if (f.is_open() == 0)
				{
					cout << "Файл не найден. Возможно, проблема в вас..." << endl;
				}
				else
				{
					q.dump(f, s.s, q.name);
				}
				f.close();
			}
			else if (s.code == 2)
			{
				for (int j = 0; j < s.a; ++j)
				{
					q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
				}
				q.printer();
			}
			else if (s.code == 3)
			{
				cout << "Серьёзно? Вы хотите убить всю жизнь в этом маленьком мирке?" << endl;
				cout << "Ну что ж, как прикажете..." << endl;
				return 0;
			}
		}
	}
	else if (argc == 6)		//Из входного в выходной
	{
		MagicWord s;
		UI q(50, 0);
		ifstream in(argv[1]);
		if (in.is_open() == 0)
		{
			cout << "Входной файл не найден. Возможно, неправильно указан путь." << endl;
			return 1;
		}

		/*
		cout << argv[0] << endl;
		cout << argv[1] << endl;
		cout << argv[2] << endl;
		cout << argv[3] << endl;
		cout << argv[4] << endl;
		cout << argv[5] << endl;
		*/

		int iterations = 0;
		if ((argv[2][0] == '-')&& (argv[2][1] == 'i'))
		{
			try { iterations = stoi(argv[3]); }
			catch (const char* error_message)
			{
				std::cout << "Непраильно введено число." << std::endl;
				return 1;
			}
		}
		else
		{
			std::cout << "Bad input. i" << std::endl;
			return 1;
		}

		if ((argv[4][0] != '-') || (argv[4][1] != 'o'))
		{
			std::cout << "Bad input. o" << std::endl;
			return 1;
		}
		q.parcer(in);
		
		for (int j = 0; j < s.a; ++j)
		{
			q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
		}
		ofstream f(argv[5]);
		if (f.is_open() == 0)
		{
			cout << "Выходной файл не найден. Возможно, неправильно проложен путь. Эхъ, не быть вам штурманом..." << endl;
		}

		q.dump(f, s.s, q.name);
        f.close();
		in.close();
	}
	else
	{
		std::cout << "Ты чаво наделал..." << std::endl;
		return 1;
	}
}
  