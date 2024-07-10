#include "MagicWord.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

MagicWord::MagicWord()
{
	s = "";
	a = 0;
	code = 0;
}

MagicWord::~MagicWord()
{
	s.clear();
	a = 0;
	code = 0;
}

MagicWord::MagicWord(std::string line)	//добавить исключение на ввод пустой строки
{
	for (int i = 0; line[i] != ' '; ++i)
	{
		s += line[i];
		if (i > 5)
		{
			//бросить exception на неправильный ввод или попросить пользователя повторить ввод
		}
	}

	if (s == "dump")			//Переделать на собственный switch-case для строк?
	{
		string s2;
		for (int i = 5; line[i] != ' '; ++i)	//exception на неправильный ввод файла и на его отсутствие
		{
			s2 += line[i];
			if (i > 10000)
			{
				//бросить exception на неправильный ввод или попросить пользователя повторить ввод
			}
		}
	}
	else if (s == "tick")
	{
		string s2;
		for (int i = 5; line[i] != ' '; ++i)	//exception на неправильный ввод файла и на его отсутствие
		{
			s2 += line[i];
			if (i > 11)
			{
				//бросить exception на неправильный ввод или попросить пользователя повторить ввод
			}
		}
		a = stoi(s2);
	}
	else if (s == "exit")
	{
		//????????
	}
	else if (s == "help")
	{
		//прописать мануал
	}
}

MagicWord & MagicWord::operator=(string line)
{
	for (int i = 0; line[i] != ' '; ++i)
	{
		s += line[i];
		if (i > 5)
		{
			//бросить exception на неправильный ввод или попросить пользователя повторить ввод
		}
	}

	if (s == "dump")			//Переделать на собственный switch-case для строк?
	{
		string s2;
		for (int i = 5; line[i] != ' '; ++i)	//exception на неправильный ввод файла и на его отсутствие
		{
			s2 += line[i];
			if (i > 10000)
			{
				//бросить exception на неправильный ввод или попросить пользователя повторить ввод
			}
		}
	}
	else if (s == "tick")
	{
		string s2;
		for (int i = 5; line[i] != ' '; ++i)	//exception на неправильный ввод файла и на его отсутствие
		{
			s2 += line[i];
			if (i > 11)
			{
				//бросить exception на неправильный ввод или попросить пользователя повторить ввод
			}
		}
		a = stoi(s2);
	}
	else if (s == "exit")
	{
		//????????
	}
	else if (s == "help")
	{
		//прописать мануал
	}
	/////Доделать
	return *this;
}


std::istream& operator>>(std::istream &s, MagicWord &m) {
	double re = 0;
	double im = 0;
	string line, s1;
	getline(s, line);
	for (int i = 0; (i < line.size()) && (line[i] != ' '); ++i)
	{
		s1 += line[i];
		if (i > 5)
		{
			cout << "ТЕБЯ КТО ЧИТАТЬ УЧИЛ??? А ну-к, открыл букварь, повторил буквы и бегом писать нормальные команды!" << endl;
			return s;
		}
	}
	
	if (s1 == "dump")			//Переделать на собственный switch-case для строк?
	{
		string s2;
		int i = 5;
		if (line[i] == '"')
		{
			i = 6;
		}
		for (; (i < line.size()) && (line[i] != ' ') && (line[i] != '"'); ++i)	//проверка на корректность файла
		{
			
			s2 += line[i];
			if (i > 10000)
			{
				cout << "Что-то длинноватый у тебя файл... Я тебе сразу скажу, SQL-инъекция не пройдёт. Не тот код)" << endl;
				return s;
			}
		}
		m.s = s1;
		m.a = 0;
		m.s = s2;
		m.code = 1;
	}
	else if (s1 == "tick")
	{
		string s2 = "";
		for (int i = 5; (i < line.size()) && (line[i] != ' '); ++i)	//добавь проверку на циферки
		{
			if ((line[i] >= '0') && (line[i] <= '9'))
			{
				s2 += line[i];
			}
			else
			{ 
				cout << "А циферки то у вас неправильные, сударь) Думаете я не вижу? Я всё вижу:)" << endl;
				return s;
			}
			
			if (i > 12)
			{
				cout << "Слышь, фраер, ты что тут, самый умный? Решил мне программу лардж тестом накрыть? А вот хрен тебе." << endl;
				return s;
			}
		}
		m.s = s1;
		if (s2 == "")
		{
			m.a = 1;
		}
		else
		{
			m.a = stoi(s2);	
		}
		m.code = 2;
	}
	else if (s1 == "exit")
	{
		m.s = s1;
		m.a = 0;
		m.code = 3;
	}
	else if (s1 == "help")
	{
		cout << "Ну здравствуй, путник. Вижу тебе понадобилась помощь? Что ж, да, помощь действительно всем нужна, особенно когда открываешь чёрный экран..." << endl;
		cout << "В общем, как ты понял, перед тобой игра в жизнь." << endl;
		cout << "Так как ты скачал и открыл эту программу, то очевидно знаешь что это, так что не буду тратить твоё время и сразу перейду к командам и самой программе." << endl;
		cout << "\033[32mПрограмма поддерживает три способа интеракции:\033[0m" << endl;
		cout << "1) Случайный. Ты запускаешь программу, я генерирую поле и дальше командуешь ты." << endl;
		cout << "2) Онлайн. Ты заранее пишешь поле в файле с необходимым форматом, подаёшь его как аргумент и творишь с ним что хочешь." << endl;
		cout << "3) Божественный. Ты заранее пишешь поле в файле с необходимым форматом, подаёшь его как аргумент, вторым аргументом пишешь количество итераций и название выходного файла, а дальше дело за мной)" << endl;
		cout << "\033[32mКоманды\033[0m" << endl;
		cout << "dump <filename> - сохранить вселенную в файл" << endl;
		cout << "tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по умолчанию 1) итераций и напечатать результат." << endl;
		cout << "exit – завершить игру" << endl;
		cout << "help – распечатать справку о командах" << endl;
		m.s = s1;
		m.a = 0;
		m.code = 4;
	}
	else
	{
		cout << "Моя твоя не понимать. Твоя писать ошибка." << endl;
	}
	return s;
}


const char * MagicWord::to_char()
{
	string s = this->s;
	int size = s.size();
	char * q = (char *)malloc(sizeof(char) * size);
	for (int i = 0; i < size; ++i)
	{
		q[i] = s[i];
	}
	return q;
}