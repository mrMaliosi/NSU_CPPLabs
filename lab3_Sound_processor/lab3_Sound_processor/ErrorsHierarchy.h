#pragma once
#include <iostream>
#include <exception>


using namespace std;

// ������� ����� ������
class Error : public std::exception {
public:
	virtual const char* what() const noexcept override {
		return "������";
	}
	virtual void exit_code() const noexcept {
		cerr << "������" << endl;
		exit (1);
	}
};

class WrongInputError : public Error {
public:
	const char* what() const noexcept override {
		return "������������ config.txt";
	}
	virtual void exit_code() const noexcept {
		cerr << "������������ config.txt" << endl;
		exit(2);
	}
};

class LargeInputError : public Error {
public:
	const char* what() const noexcept override {
		return "������� ������� ��������� � config.txt";		
	}
	virtual void exit_code() const noexcept {
		cerr << "������� ������� ��������� � config.txt" << endl;
		exit(3);
	}
};

class ArgumentsError : public Error {
public:
	const char* what() const noexcept override {
		return "����������� ������ ���������";
	}
	virtual void exit_code() const noexcept {
		cerr << "����������� ������ ���������" << endl;
		exit(4);
	}
};

class FileSearchError : public Error {
public:
	const char* what() const noexcept override {
		return "�� ������ ����� ����";
	}
	virtual void exit_code() const noexcept {
		cerr << "�� ������ ����� ����" << endl;
		exit(5);
	}
};

class WavParsingError : public Error {
public:
	const char* what() const noexcept override {
		return "������ ��������� wav �����";
	}
	virtual void exit_code() const noexcept {
		cerr << "������ ��������� wav �����" << endl;
		exit(6);
	}
};

