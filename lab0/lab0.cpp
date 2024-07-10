#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector <pair <std::string, unsigned> > q;

bool great(pair <string, unsigned> a, pair <string, unsigned> b) {
	return b.second < a.second;
}

int main(int argc, char* argv[]) {
	if (argc < 3)
	{
		std::cout << "Fatal error. Not enough input arguments." << std::endl;
		return 1;
	}
	else if (argc > 3)
	{
		std::cout << "Fatal error. Too much input arguments." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Conversion has started..." << std::endl;
	}

	std::ifstream in(argv[1]); // открываем файл для чтения
	std::map<std::string, unsigned> frequency_table;
	string word;
	if (in.is_open())
	{
		while (std::getline(in, word, ' '))
		{
			++frequency_table[word];
		}
	}
	in.close();     // закрываем файл


	//pair <string, unsigned> p;
	int n = 0;                                              //число уникальных слов
	for (const auto&pair1 : frequency_table)
	{
		q.push_back(pair1);
		++n;
	}

	sort(q.begin(), q.end(), great);

	ofstream out;               //поток для записи
	out.open(argv[2]);
	for (int i = 0; i < n; ++i)
	{
		out << q[i].first << ";" << q[i].second << "\n";
	}


	out.close();
	return 0;
}
