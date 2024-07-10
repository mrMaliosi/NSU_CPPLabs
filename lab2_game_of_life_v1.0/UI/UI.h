#pragma once
#include "../field/field.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class UI : public field
{
public:
	int born_rule1;
	int born_rule2;
	int survival_rule1;
	int survival_rule2;
	string name;

	UI();
	UI(int n, int f);
	~UI();
	void parcer(ifstream & f);
};