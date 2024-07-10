#pragma once
#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

class field
{
protected:
	std::unique_ptr<int[]> square_;
	int N_;
	int size_;
public:
	field();
	field(int n, int f);
	~field();

	void next_tick(int born_rule1, int born_rule2, int survival_rule1, int survival_rule2);
	void dump(ofstream &f, string name, string rule);
	void printer();
};
	