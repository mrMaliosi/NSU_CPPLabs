#pragma once
#include <iostream>

using namespace std;

typedef struct Data
{
	int code;
	int data1;
	int data2;
} Data;

//������ + ��������� ��� �������� ���������� � �����
class Parser
{
public:
	Data data_;
	Parser(std::istream &s);
	~Parser();
};